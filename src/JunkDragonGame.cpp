#include "JunkDragonGame.hpp"
#include <iostream>
#include "GameObject.hpp"
#include "sre/RenderPass.hpp"
#include "SpriteComponent.hpp"
#include "AnimationControllerComponent.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "PhysicsComponent.hpp"
#include "FloatTrackComponent.hpp"
#include <sre/Inspector.hpp>
#include <math.h>
#include "DragonController.hpp"
#include "FireBallController.hpp"
#include "BurnableComponent.hpp"
#include "PickUpComponent.hpp"
#include "Command.hpp"
#include "AudioManager.hpp"
#include "PlayingState.hpp"
#include "EndState.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

const glm::vec2 JunkDragonGame::windowSize(INT_WINDOWSIZE_HEIGHT, INT_WINDOWSIZE_WIDTH);
JunkDragonGame* JunkDragonGame::instance = nullptr;

JunkDragonGame::JunkDragonGame():debugDraw(physicsScale) {
    
    instance = this;
    
    r.setWindowSize(windowSize);
    r.init()
    .withSdlInitFlags(SDL_INIT_EVERYTHING)
    .withSdlWindowFlags(SDL_WINDOW_OPENGL);
    
    init();
    
    new AudioManager();
    
    buildGUI();

    r.keyEvent = [&](SDL_Event& e){
        onKey(e);
    };
    
    r.frameUpdate = [&](float deltaTime){
       update(deltaTime);
    };
    r.frameRender = [&](){
        render();    };

    // start game loop
    r.startEventLoop();
}

void JunkDragonGame::buildGUI() {
    auto fuelTrackerObj = createGameObject();
    fuelTrackComp = fuelTrackerObj->addComponent<FloatTrackComponent>();
    fuelTrackComp->init("Fuel", dragonObj->getComponent<DragonController>()->getFuel(), {0.0f, 0.9f}, {0.3f,0.1f});

    auto timeTrackerObj = createGameObject();
    timeTrackComp = timeTrackerObj->addComponent<FloatTrackComponent>();
    timeTrackComp->init("time", time_remaining, {0.0f, 0.8f}, {0.3f, 0.1f} );

    auto scoreTrackerObj = createGameObject();
    scoreTrackComp = fuelTrackerObj->addComponent<FloatTrackComponent>();
    scoreTrackComp->init("Score", dragonObj->getComponent<DragonController>()->getFuel(), {0.7f, 0.9f}, {0.3f, 0.1f} );

    auto houseTrackerObj = createGameObject();
    houseTrackComp = houseTrackerObj->addComponent<FloatTrackComponent>();
    houseTrackComp->init("Houses", (float)n_houses, {0.7f, 0.8f}, {0.3f, 0.1f} );
}

void JunkDragonGame::init(){
    initPhysics();
    
    gs_playingstate = std::shared_ptr<GameState>( new PlayingState() );
    gs_endstate     = std::shared_ptr<GameState>( new EndState() );
    changeState(gs_playingstate);
    

    score                   = 0.0f;
    burnination_has_begun   = false;
    time_elapsed            = 0.0f;
    n_houses                = 0;
    time_remaining          = 10.0f;
    game_over               = false;

    // Spritesheet for the game
    spriteAtlas = sre::SpriteAtlas::create("junkdragon.json","junkdragon.png");

    currentLevel = std::make_shared<Level>();
    currentLevel->LoadLevel("level1");
    
    createWalls(currentLevel->GetWallDimensions(), INT_WALL_THICKNESS);
    
    // Camera Object
    auto camObj = createGameObject();
    camera = camObj->addComponent<CameraFollow>();
    
    
    // Dragon Game Object (Player)
    dragonObj = createGameObject();
    dragonObj->name = "Dragon";
    camera->setFollowObject(dragonObj, {0,0});
    glm::vec2 spawnPosition = currentLevel->GetStartingPosition();
    dragonObj->setPosition(spawnPosition);
    dragonObj->setRotation(F_ROTATION_NORTH);

    auto dragonC = dragonObj->addComponent<DragonController>();
    
    auto sprite = spriteAtlas->get("dragon_11.png");
    sprite.setScale({3,3});
    sprite.setOrderInBatch(U_DRAGON_LAYER);
    auto spriteC = dragonObj->addComponent<SpriteComponent>();
    spriteC->setSprite(sprite);
    
    auto animCC = dragonObj->addComponent<AnimationControllerComponent>();
    animCC->setLayer(U_DRAGON_LAYER);

    animCC->addState(
        "flying",
        0.4f,
        { spriteAtlas->get("dragon_11.png"), spriteAtlas->get("dragon_12.png"), spriteAtlas->get("dragon_11.png"), spriteAtlas->get("dragon_10.png") }
        );

    animCC->setScale({INT_DRAGON_SCALE,INT_DRAGON_SCALE});
    animCC->setState("flying");
    dragonC->SetAnimationControllerComponent( animCC );
    
    auto DragonPhysics = dragonObj->addComponent<PhysicsComponent>();
    dragonC->setPhysicsComponent(dragonObj->getComponent<PhysicsComponent>());

    DragonPhysics->initCircle(b2_dynamicBody, 30/physicsScale, dragonObj->getPosition()/physicsScale, dragonObj->getRotation(), 1);

    // Add background
    backgroundComponent.init("background.png", {INT_BACKGROUND_STARTPOS,INT_BACKGROUND_STARTPOS}, 
        {INT_BACKGROUND_SIZE, INT_BACKGROUND_SIZE}, INT_BACKGROUND_RESOLUTION);
    
    // Add Houses
    std::vector<glm::vec2> houses = currentLevel->GetHousePositions();
    for (int i = 0; i < houses.size(); i++) {
        createHouse(houses[i]);
    }
    
    // Add pickups
    createPickUp({500, 400}, spriteAtlas->get("chilli.png"), Command( dragonC->self, &DragonController::addFuel ) );
    createPickUp({700, 800}, spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    createPickUp({1100, 200}, spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    createPickUp({400, -300}, spriteAtlas->get("pizza.png"), Command( dragonC->self, &DragonController::addFuel ) );  

    createPickUp({900, -400}, spriteAtlas->get("chilli.png"), Command( dragonC->self, &DragonController::addFuel ) );
    createPickUp({-300, 400}, spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    createPickUp({-800, 500}, spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    createPickUp({-1000, -100}, spriteAtlas->get("pizza.png"), Command( dragonC->self, &DragonController::addFuel ) );   
}

void JunkDragonGame::update(float time){
    gs_currentstate->update(time);
    
    for (int i=0;i<sceneObjects.size();i++){
        sceneObjects[i]->update(time);
        if (sceneObjects[i]->getDeleteMe()) {
            sceneObjects.erase(sceneObjects.begin() + i);
        }
    }

    // Update GUI elements last
    fuelTrackComp->setVal( dragonObj->getComponent<DragonController>()->getFuel() );
    scoreTrackComp->setVal( this->score );
    houseTrackComp->setVal( this->n_houses );
    timeTrackComp->setVal(this->time_remaining);


    if( !game_over && checkGameOver() ) {
            game_over = true;
            changeState(gs_endstate);
    } else {
        time_remaining = fmax(time_remaining - time, 0.0f);
    }
    
}

void JunkDragonGame::render() {
    auto rp = sre::RenderPass::create()
    .withCamera(camera->getCamera())
    .build();
    
    backgroundComponent.renderBackground(rp,0.0f);
    
    auto spriteBatchBuilder = sre::SpriteBatch::create();
    
    for (auto & go : sceneObjects){
        go->renderSprite(spriteBatchBuilder);
    }
    
    auto sb = spriteBatchBuilder.build();
    rp.draw(sb);

    if (doDebugDraw){
        static sre::Inspector profiler;
        profiler.update();
        profiler.gui(false);

        world->DrawDebugData();
        rp.drawLines(debugDraw.getLines());
        debugDraw.clear();
    }

    // Render the GUI components last
    for (auto & go : sceneObjects){
        for (auto & comp : go->getComponents()){
            comp->onGui();
        }
    }

    // TODO put everything into the gamestate render function
    gs_currentstate->render();
}

void JunkDragonGame::updatePhysics() {
    const int positionIterations = INT_POSITION_ITERATIONS;
    const int velocityIterations = INT_VELOCITY_ITERATIONS;
    world->Step(timeStep, velocityIterations, positionIterations);

    for (auto phys : physicsComponentLookup) {
        PhysicsComponent* physicsComponent = phys.second;
        if (physicsComponent->isAutoUpdate() == false) continue;
        auto position = physicsComponent->getBody()->GetPosition();
        float angle = physicsComponent->getBody()->GetAngle();
        auto gameObject = physicsComponent->getGameObject();
        gameObject->setPosition(glm::vec2(position.x*physicsScale, position.y*physicsScale));
        gameObject->setRotation(angle);
    }
}


void JunkDragonGame::initPhysics() {
    float gravity = F_GRAVITY;
    delete world;
    world = new b2World(b2Vec2(0,gravity));
    world->SetContactListener(this);

    if (doDebugDraw){
        world->SetDebugDraw(&debugDraw);
    }
}

void JunkDragonGame::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);
    handleContact(contact, true);
}

void JunkDragonGame::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
    handleContact(contact, false);
}

void JunkDragonGame::increaseScore(float i_score) {
    this->score += i_score;
}

void JunkDragonGame::decrementHouses() {
    this->n_houses--;
}

void JunkDragonGame::handleContact(b2Contact *contact, bool begin) {
    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
    auto physA = physicsComponentLookup.find(fixA);
    auto physB = physicsComponentLookup.find(fixB);
    if (physA !=physicsComponentLookup.end() && physB != physicsComponentLookup.end()){
        auto & aComponents = physA->second->getGameObject()->getComponents();
        auto & bComponents = physB->second->getGameObject()->getComponents();
        for (auto & c : aComponents){
            if (begin){
                c->onCollisionStart(physB->second);
            } else {
                c->onCollisionEnd(physB->second);
            }
        }
        for (auto & c : bComponents){
            if (begin){
                c->onCollisionStart(physA->second);
            } else {
                c->onCollisionEnd(physA->second);
            }
        }
    }
}

void JunkDragonGame::registerPhysicsComponent(PhysicsComponent *r) {
    physicsComponentLookup[r->getFixture()] = r;
}

void JunkDragonGame::deregisterPhysicsComponent(PhysicsComponent *r) {
    auto iter = physicsComponentLookup.find(r->getFixture());
    if (iter != physicsComponentLookup.end()){
        physicsComponentLookup.erase(iter);
    } else {
        assert(false); // cannot find physics object
    }
}

void JunkDragonGame::onKey(SDL_Event &event) {
    for (auto & gameObject: sceneObjects) {
        for (auto & c : gameObject->getComponents()){
            bool consumed = c->onKey(event);
            if (consumed){
                return;
            }
        }
    }

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_z:
                break;
            case SDLK_d:
                // press 'd' for physics debug
                doDebugDraw = !doDebugDraw;
                if (doDebugDraw){
                    world->SetDebugDraw(&debugDraw);
                } else {
                    world->SetDebugDraw(nullptr);
                }
                break;
        }
    }
}

std::shared_ptr<GameObject> JunkDragonGame::createGameObject() {
    auto obj = std::shared_ptr<GameObject>(new GameObject());
    sceneObjects.push_back(obj);
    return obj;
}

void JunkDragonGame::createFireBall( ) {
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



void JunkDragonGame::createHouse( glm::vec2 pos ) {
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
        0.2f,
        {spriteAtlas->get("farmhouse_2_burn1.png"), spriteAtlas->get("farmhouse_2_burn2.png")}
        );
    houseACC->addState(
        "singed",
        1.0f,
        {spriteAtlas->get("farmhouse_3.png")}
        );
    houseACC->addState(
        "singed_onfire",
        0.2f,
        {spriteAtlas->get("farmhouse_3_burn1.png"), spriteAtlas->get("farmhouse_3_burn2.png")}
        );
    
    houseACC->setScale({1,1});
    houseACC->setState("notburning");
    houseACC->setLayer(U_GROUND_LAYER);

    houseBC->SetAnimationControllerComponent( houseACC );

    // Game Junk
    n_houses++;
}

void JunkDragonGame::createPickUp(glm::vec2 pos, sre::Sprite pickUpSprite, Command cmd) {
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

void JunkDragonGame::createWalls(glm::vec2 dimensions, int thickness){
    wallTop = createGameObject();
    wallBottom = createGameObject();
    wallLeft = createGameObject();
    wallRight = createGameObject();
    auto levelPhysT = wallTop->addComponent<PhysicsComponent>();
    auto levelPhysB = wallBottom->addComponent<PhysicsComponent>();
    auto levelPhysL = wallLeft->addComponent<PhysicsComponent>();
    auto levelPhysR = wallRight->addComponent<PhysicsComponent>();
    
    levelPhysT->initBox(b2_staticBody, glm::vec2 {(dimensions.x + thickness)/physicsScale,thickness/physicsScale}, glm::vec2 {0,(dimensions.y+thickness)/physicsScale}, 1);
    levelPhysB->initBox(b2_staticBody, glm::vec2 {(dimensions.x + thickness)/physicsScale,thickness/physicsScale}, glm::vec2 {0,-(dimensions.y+thickness)/physicsScale}, 1);
    
    levelPhysL->initBox(b2_staticBody, glm::vec2 {thickness/physicsScale,dimensions.y/physicsScale}, glm::vec2 {-dimensions.x/physicsScale,0}, 1);
    levelPhysR->initBox(b2_staticBody, glm::vec2 {thickness/physicsScale,dimensions.y/physicsScale}, glm::vec2 {dimensions.x/physicsScale,0}, 1);
}

bool JunkDragonGame::checkGameOver() {
    if (n_houses == 0) {
        return true;
    }

    if (time_remaining <= 0.0f) {
        return true;
    }

    return false;
}

void JunkDragonGame::changeState( std::shared_ptr<GameState> gs_state ) {
    gs_nextstate = gs_state;

    if(gs_currentstate != nullptr) {
        gs_currentstate->exitState();
    }
    gs_nextstate->enterState();

    gs_currentstate = gs_nextstate;
    gs_nextstate = nullptr;

}