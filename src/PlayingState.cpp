//
//  PlayingState.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "JunkDragonGame.hpp"
#include "PhysicsComponent.hpp"
#include "PlayingState.hpp"
#include "AudioManager.hpp"

#include "DragonController.hpp"
#include "FireBallController.hpp"
#include "BurnableComponent.hpp"
#include "PickUpComponent.hpp"

#include "AnimationControllerComponent.hpp"
#include "SpriteComponent.hpp"
#include "GameObject.hpp"   

#include "Command.hpp"
#include <iostream>
#include <cassert>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

void PlayingState::enterState() {
    std::cout << "PLAYING STATE" << std::endl;

    // Spritesheet for the game
    if(!isLoaded){
        spriteAtlas = sre::SpriteAtlas::create("junkdragon.json","junkdragon.png");
        isLoaded = true;
    }

    createCamera();

    current_level = std::make_shared<Level>();
    assert(next_level_to_load != "_");
    std::cout << "next level is: " << next_level_to_load << std::endl;
    current_level->LoadLevel( next_level_to_load );
    
    LevelValues level_values = current_level->GetLevelValues();
    
    burnination_has_begun   = false;
    time_elapsed            = 0.0f;
    time_remaining          = level_values.time;
    game_over               = false;
    score                   = best_score;
    n_houses = 0;
    
    command_map["chilli.png"] = Command(this, &PlayingState::addFuelToDragon);
    command_map["pizza.png"] = Command(this, &PlayingState::addFuelToDragon);
    command_map["milk.png"] = Command(this, &PlayingState::removeFuelFromDragon);
    command_map["donut.png"] = Command(this, &PlayingState::fasterDragon);
    
    if (!Mix_PlayingMusic()) {
        AudioManager::instance->PlayMusic();
    }
    
    if (!AudioManager::instance->getIsLoaded()) {
        AudioManager::instance->LoadSoundChunks();
    }
    
    
    
    
    // build the level
    createDragon( level_values.starting_position );
    camera->setFollowObject(dragonObj, {0.0f,0.0f});

    createWalls(level_values.wall_dimensions, INT_WALL_THICKNESS);

    // Add Houses 
    for (int i = 0; i < level_values.house_positions.size(); i++) {
        createHouse(level_values.house_positions[i]);
    }
    
    // Add pick-ups
    for (int i = 0; i<level_values.pick_up_positions.size(); i++) {
        createPickUp(level_values.pick_up_positions[i], spriteAtlas->get(level_values.pick_up_sprite[i]), command_map[level_values.pick_up_sprite[i]] );
    }
    
    // Add background
    if( !backgroundComponent.getIsLoaded() ) {
        backgroundComponent.init("background.png");
    }
    backgroundComponent.buildBackground( -level_values.wall_dimensions,
        2.0f*level_values.wall_dimensions, INT_BACKGROUND_RESOLUTION, INT_WALL_THICKNESS);

    buildGUI();

    timeTrackComp = guiObj->addComponent<SingleVarGuiComponent>();
    timeTrackComp->init("time", time_remaining, {0.0f, 0.8f}, {0.2f, 0.1f} );

    scoreTrackComp = guiObj->addComponent<SingleVarGuiComponent>();
    scoreTrackComp->init("score", score, {0.8f, 0.9f}, {0.2f, 0.1f} );

    houseTrackComp = guiObj->addComponent<SingleVarGuiComponent>();
    houseTrackComp->init("Houses", n_houses, {0.8f, 0.8f}, {0.2f, 0.1f} );
}

void PlayingState::createCamera( ) {
    // Camera Object
    camObj = std::shared_ptr<GameObject>(new GameObject());
    camera = camObj->addComponent<CameraFollow>();
    camera->setFollowObject(nullptr, {0,0});
}

void PlayingState::setScore( float score ) {
    this->best_score = score;
}

void PlayingState::exitState() {
    camera->unsetFollowObject();
    if(Mix_PlayingMusic()){ Mix_HaltMusic();};
    //AudioManager::instance->UnloadSoundChunks();
    // WALLS

    dragonObj = nullptr;

    backgroundComponent.terminate();

    current_level = nullptr;
    // spriteAtlas.reset();

    guiObj->removeComponent(timeTrackComp);
    guiObj->removeComponent(scoreTrackComp);
    guiObj->removeComponent(houseTrackComp);
    guiObj          = nullptr;

    sceneObjects.erase(sceneObjects.begin(), sceneObjects.end());
}

void PlayingState::update( float time ) {

    if (checkGameOver()) {
        if (n_houses == 0) {
            best_score = score;
            JunkDragonGame::instance->incrementLevel();
            JunkDragonGame::instance->transition();
        }
        
        if (time_remaining <= 0.0f) {
            JunkDragonGame::instance->recordScore(score);
            JunkDragonGame::instance->endTheGame();
        }
    }

    camObj->update(time);

    time_remaining = fmax(time_remaining - time, 0.0f);

    JunkDragonGame::instance->updatePhysics();
    if (time > F_PHYSICS_TIMESTEP) // if framerate approx 30 fps then run two physics steps
    {
        JunkDragonGame::instance->updatePhysics();
    }

    for (int i=0;i<sceneObjects.size();i++){
        sceneObjects[i]->update(time);
        if (sceneObjects[i]->getDeleteMe()) {
            sceneObjects.erase(sceneObjects.begin() + i);
        }
    }
    // update gui elements
    timeTrackComp->setVal(time_remaining);
    scoreTrackComp->setVal(score);
    houseTrackComp->setVal(n_houses);
    
}

void PlayingState::render( sre::RenderPass &renderPass  ) {
    // wallTop->getComponent<WallTileComponent>()->renderWalls(renderPass);
}

bool PlayingState::checkGameOver() {
    if (n_houses == 0) {
        return true;
    }

    if (time_remaining <= 0.0f) {
        return true;
    }

    return false;
}

bool PlayingState::onKey(SDL_Event &event) {

    return false;
}

void PlayingState::setNextLevelToLoad(std::string next_level) {
    next_level_to_load = next_level;
}

void PlayingState::createDragon( glm::vec2 starting_position ) {
    // Dragon Game Object (Player)
    dragonObj = createGameObject();
    dragonObj->name = "Dragon";
    glm::vec2 spawnPosition = starting_position;
    dragonObj->setPosition(spawnPosition);
    dragonObj->setRotation(F_ROTATION_NORTH);

    auto dragonC = dragonObj->addComponent<DragonController>();
    dragonC->setFireballCmd( Command(this, &PlayingState::createFireBall ) );
    
    auto sprite = spriteAtlas->get("dragon_11.png");
    sprite.setScale({3,3});
    sprite.setOrderInBatch(U_DRAGON_LAYER);
    auto spriteC = dragonObj->addComponent<SpriteComponent>();
    spriteC->setSprite(sprite);
    
    auto animCC = dragonObj->addComponent<AnimationControllerComponent>();
    animCC->setLayer(U_DRAGON_LAYER);

    animCC->addState(
        "flying",
        0.2f,
        { spriteAtlas->get("dragon_11.png"), spriteAtlas->get("dragon_12.png"), spriteAtlas->get("dragon_11.png"), spriteAtlas->get("dragon_10.png") }
        );

    animCC->setScale({INT_DRAGON_SCALE,INT_DRAGON_SCALE});
    animCC->setState("flying");
    dragonC->SetAnimationControllerComponent( animCC );
    
    auto DragonPhysics = dragonObj->addComponent<PhysicsComponent>();
    dragonC->setPhysicsComponent(dragonObj->getComponent<PhysicsComponent>());

    DragonPhysics->initCircle(b2_dynamicBody, 60/physicsScale, dragonObj->getPosition()/physicsScale, dragonObj->getRotation(), 1);
                    
    // Track fuel with gui element Gui Element
    dragonObj->addComponent<SingleVarGuiComponent>();
    dragonObj->getComponent<SingleVarGuiComponent>()->init("Fuel", dragonC->getFuel(), {0.0f, 0.9f}, {0.2f,0.1f});
}

void PlayingState::createFireBall( ) {
    auto fireballObj = createGameObject();
    fireballObj->name = "Fireball";

    auto trajectory = glm::rotateZ(glm::vec3(0,1.0f,0), glm::radians(dragonObj->getRotation() ));
    fireballObj->setPosition( dragonObj->getPosition() + (glm::vec2)(trajectory * F_FIREBALL_OFFSET) );
    fireballObj->setRotation( dragonObj->getRotation() );

    auto fireballController = fireballObj->addComponent<FireBallController>();

    auto fireballSprite = spriteAtlas->get("fireball_3.png");
    
    fireballSprite.setScale({0.9,0.9});
    auto fireballSpriteComponent = fireballObj->addComponent<SpriteComponent>();
    fireballSpriteComponent->setSprite(fireballSprite);

    auto fireballACC = fireballObj->addComponent<AnimationControllerComponent>();

    // Could animate the not burning buildings
    fireballACC->addState(
        "shooting",
        0.1f,
        {spriteAtlas->get("fireball_1.png"),spriteAtlas->get("fireball_2.png"),spriteAtlas->get("fireball_3.png"),spriteAtlas->get("fireball_4.png")}
        );

    fireballACC->setScale({0.9,0.9});
    fireballACC->setState("shooting");
    fireballACC->setLayer(U_FIREBALL_LAYER);

    auto fireballPhysics = fireballObj->addComponent<PhysicsComponent>();
    fireballPhysics->initCircle(b2_dynamicBody, 20/physicsScale, fireballObj->getPosition()/physicsScale, fireballObj->getRotation(), 1);

    fireballPhysics->setLinearVelocity( trajectory * fireballController->getSpeed() );
}

void PlayingState::houseBurnedDown() {
    score += 100.0f;
    n_houses--;
}

void PlayingState::addFuelToDragon() {
    dragonObj->getComponent<DragonController>()->addFuel( 10.0f );
    AudioManager::instance->PlaySound(AudioManager::pick_up);
}

void PlayingState::removeFuelFromDragon() {
    dragonObj->getComponent<DragonController>()->removeFuel(10);
    AudioManager::instance->PlaySound(AudioManager::power_down);
}

void PlayingState::fasterDragon() {
    dragonObj->getComponent<DragonController>()->addSpeedBoost();
    AudioManager::instance->PlaySound(AudioManager::pick_up);
}

void PlayingState::createHouse( glm::vec2 pos ) {
    auto HouseObj = createGameObject();
    HouseObj->name = "House";
    HouseObj->setPosition(pos);
    HouseObj->setRotation(F_ROTATION_NORTH);
    auto houseSprite = spriteAtlas->get("farmhouse_2.png");
    houseSprite.setOrderInBatch(U_GROUND_LAYER);
    auto houseSpriteC = HouseObj->addComponent<SpriteComponent>();
    houseSprite.setScale({1,1});
    houseSpriteC->setSprite(houseSprite);
    auto houseBC = HouseObj->addComponent<BurnableComponent>();
    houseBC->setBurnCmd( Command( this, &PlayingState::houseBurnedDown ) );
    
    auto HousePhysics = HouseObj->addComponent<PhysicsComponent>();
    HousePhysics->initCircle(b2_staticBody, 70/physicsScale, HouseObj->getPosition()/physicsScale, HouseObj->getRotation(), 1);
    HousePhysics->setSensor(true);

    auto houseACC = HouseObj->addComponent<AnimationControllerComponent>();

    // Could animate the not burning buildings
    houseACC->addState(
        "notburning",
        1.0f,
        {spriteAtlas->get("farmhouse_2.png")}
        );
    houseACC->addState(
        "onfire",
        0.15f,
        {spriteAtlas->get("farmhouse_2_burn1.png"), spriteAtlas->get("farmhouse_2_burn2.png")}
        );
    houseACC->addState(
        "singed",
        1.0f,
        {spriteAtlas->get("farmhouse_3.png")}
        );
    houseACC->addState(
        "singed_onfire",
        0.15f,
        {spriteAtlas->get("farmhouse_3_burn1.png"), spriteAtlas->get("farmhouse_3_burn2.png")}
        );
    
    houseACC->setScale({1,1});
    houseACC->setState("notburning");
    houseACC->setLayer(U_GROUND_LAYER);

    houseBC->SetAnimationControllerComponent( houseACC );

    // Game Junk
    n_houses++;
}

void PlayingState::createPickUp(glm::vec2 pos,sre::Sprite pickUpSprite, Command cmd) {
    auto PUObj = createGameObject();
    PUObj->setPosition(pos);
    PUObj->setRotation(F_ROTATION_NORTH);
    pickUpSprite.setScale({0.5,0.5});
    pickUpSprite.setOrderInBatch(U_POWERUP_LAYER);
    auto PUSpriteC = PUObj->addComponent<SpriteComponent>();
    PUSpriteC->setSprite(pickUpSprite);
    auto pickUpC = PUObj->addComponent<PickUpComponent>();
    pickUpC -> SetCommand( cmd );
    
    auto PUPhys = PUObj->addComponent<PhysicsComponent>();
    PUPhys->initCircle(b2_staticBody, 40/physicsScale, PUObj->getPosition()/physicsScale, PUObj->getRotation(), 1);
    PUPhys->setSensor(true);
}

void PlayingState::createWalls(glm::vec2 dimensions, int thickness){
    wallTop = createGameObject();
    wallTop->setPosition( glm::vec2 {0,(dimensions.y+thickness)});
    
    wallBottom = createGameObject();
    wallBottom->setPosition(glm::vec2 {0,-(dimensions.y+thickness)});
    
    wallLeft = createGameObject();
    wallLeft->setPosition(glm::vec2 {-dimensions.x,0});
    
    wallRight = createGameObject();
    wallRight->setPosition(glm::vec2 {dimensions.x,0});
    
    auto levelPhysT = wallTop->addComponent<PhysicsComponent>();
    auto levelPhysB = wallBottom->addComponent<PhysicsComponent>();
    auto levelPhysL = wallLeft->addComponent<PhysicsComponent>();
    auto levelPhysR = wallRight->addComponent<PhysicsComponent>();
    
    levelPhysT->initBox(b2_staticBody, glm::vec2 {(dimensions.x + thickness)/physicsScale,thickness/physicsScale}, wallTop->getPosition()/physicsScale, 1);
    levelPhysB->initBox(b2_staticBody, glm::vec2 {(dimensions.x + thickness)/physicsScale,thickness/physicsScale}, wallBottom->getPosition()/physicsScale, 1);
    
    levelPhysL->initBox(b2_staticBody, glm::vec2 {thickness/physicsScale,dimensions.y/physicsScale}, wallLeft->getPosition()/physicsScale, 1);
    levelPhysR->initBox(b2_staticBody, glm::vec2 {thickness/physicsScale,dimensions.y/physicsScale}, wallRight->getPosition()/physicsScale, 1);
}

void PlayingState::buildGUI() {

    guiObj = createGameObject();

}
