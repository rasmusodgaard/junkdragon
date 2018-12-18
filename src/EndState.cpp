//
//  EndState.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "JunkDragonGame.hpp"
#include "EndState.hpp"
#include <iostream>

void EndState::enterState() {
    std::cout << "END STATE" << std::endl;
    createCamera();
    buildGUI();

    high_score_comp = guiObj->addComponent<FloatTrackComponent>();
    high_score_comp->init( "High score:", new_score, {0.375f, 0.45f}, {0.3f,0.1f} );
}

void EndState::exitState() {
    guiObj->removeComponent(high_score_comp);
    high_score_comp = nullptr;
    guiObj          = nullptr;
}

void EndState::update( float time ) {
    
}

void EndState::render() {
    
}

void EndState::createCamera( ) {
    // Camera Object
    camObj = std::shared_ptr<GameObject>(new GameObject());
    camera = camObj->addComponent<CameraFollow>();
    camera->setFollowObject(nullptr, {0,0});
}

bool EndState::onKey(SDL_Event &event) {

    if (event.key.keysym.sym == SDLK_SPACE) {
        if (event.type == SDL_KEYDOWN) {
            JunkDragonGame::instance->startTheGame();
        }
    }

    return false;
}

void EndState::recordScore( float final_score ) {
    new_score = final_score;
}

void EndState::buildGUI() {

    guiObj = createGameObject();

}