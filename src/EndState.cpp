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
}

void EndState::exitState() {
    
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