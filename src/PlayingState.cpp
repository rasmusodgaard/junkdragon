//
//  PlayingState.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "JunkDragonGame.hpp"
#include "PhysicsComponent.hpp"
#include "PlayingState.hpp"
#include <iostream>
#include <cassert>

void PlayingState::enterState() {
    std::cout << "PLAYING STATE" << std::endl;

    score                   = 0.0f;
    burnination_has_begun   = false;
    time_elapsed            = 0.0f;
    time_remaining          = 1.0f;
    game_over               = false;

    current_level = std::make_shared<Level>();
    assert(next_level_to_load != "_");
    current_level->LoadLevel( next_level_to_load );
    
    // build the level
    JunkDragonGame::instance->createDragon( current_level->GetStartingPosition() );
    JunkDragonGame::instance->camera->setFollowObject(JunkDragonGame::instance->dragonObj, {0.0f,0.0f});

    glm::vec2 wall_dimensions = current_level->GetWallDimensions();
    JunkDragonGame::instance->createWalls(wall_dimensions, INT_WALL_THICKNESS);

    // Add Houses
    std::vector<glm::vec2> houses = current_level->GetHousePositions();
    for (int i = 0; i < houses.size(); i++) {
        JunkDragonGame::instance->createHouse(houses[i]);
    }

    // // Add background
    JunkDragonGame::instance->backgroundComponent.init("background.png", {-wall_dimensions.x,-wall_dimensions.y}, 
        {2.0f*wall_dimensions.x, 2.0f*wall_dimensions.y}, INT_BACKGROUND_RESOLUTION);
    
    // if (auto dragonC = dragonObj->getComponent<DragonController>() ) {
    //     // Add pickups
    //     JunkDragonGame::instance->createPickUp({500, 400}, JunkDragonGame::instance->spriteAtlas->get("chilli.png"), Command( dragonC->self, &DragonController::addFuel ) );
    //     JunkDragonGame::instance->createPickUp({700, 800}, JunkDragonGame::instance->spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    //     JunkDragonGame::instance->createPickUp({1100, 200}, JunkDragonGame::instance->spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    //     JunkDragonGame::instance->createPickUp({400, -300}, JunkDragonGame::instance->spriteAtlas->get("pizza.png"), Command( dragonC->self, &DragonController::addFuel ) );  

    //     JunkDragonGame::instance->createPickUp({900, -400}, JunkDragonGame::instance->spriteAtlas->get("chilli.png"), Command( dragonC->self, &DragonController::addFuel ) );
    //     JunkDragonGame::instance->createPickUp({-300, 400}, JunkDragonGame::instance->spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    //     JunkDragonGame::instance->createPickUp({-800, 500}, JunkDragonGame::instance->spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    //     JunkDragonGame::instance->createPickUp({-1000, -100}, JunkDragonGame::instance->spriteAtlas->get("pizza.png"), Command( dragonC->self, &DragonController::addFuel ) );   
    // }
}

void PlayingState::exitState() {
    
    JunkDragonGame::instance->sceneObjects.erase(JunkDragonGame::instance->sceneObjects.begin(), JunkDragonGame::instance->sceneObjects.end());
    JunkDragonGame::instance->camera->unsetFollowObject();

    // WALLS
    JunkDragonGame::instance->dragonObj = nullptr;
    JunkDragonGame::instance->wallTop = nullptr;
    JunkDragonGame::instance->wallLeft = nullptr;
    JunkDragonGame::instance->wallRight = nullptr;
    JunkDragonGame::instance->wallBottom = nullptr;

    JunkDragonGame::instance->backgroundComponent.terminate();

    current_level = nullptr;

}

void PlayingState::update( float time ) {

    if( !game_over && checkGameOver() ) {
            game_over = true;
            JunkDragonGame::instance->endTheGame();
    } else {
        time_remaining = fmax(time_remaining - time, 0.0f);

        JunkDragonGame::instance->updatePhysics();
        if (time > F_PHYSICS_TIMESTEP) // if framerate approx 30 fps then run two physics steps
        {
            JunkDragonGame::instance->updatePhysics();
        }

        for (int i=0;i<JunkDragonGame::instance->sceneObjects.size();i++){
            JunkDragonGame::instance->sceneObjects[i]->update(time);
            if (JunkDragonGame::instance->sceneObjects[i]->getDeleteMe()) {
                JunkDragonGame::instance->sceneObjects.erase(JunkDragonGame::instance->sceneObjects.begin() + i);
            }
        }
    }
}

void PlayingState::render() {
    
}

bool PlayingState::checkGameOver() {
    // if (JunkDragonGame::instance->n_houses == 0) {
    //     return true;
    // }

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

