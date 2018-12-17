//
//  StateState.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "JunkDragonGame.hpp"
#include "StartState.hpp"
#include <iostream>

void StartState::enterState() {
    std::cout << "START STATE" << std::endl;
    createCamera();
}

void StartState::exitState() {
    
}

void StartState::update( float time ) {
    
}

void StartState::render() {
    
}

void StartState::createCamera( ) {
    // Camera Object
    camObj = std::shared_ptr<GameObject>(new GameObject());
    camera = camObj->addComponent<CameraFollow>();
    camera->setFollowObject(nullptr, {0,0});
}

bool StartState::onKey(SDL_Event &event) {

    if (event.key.keysym.sym == SDLK_SPACE) {
        if (event.type == SDL_KEYDOWN) {
            JunkDragonGame::instance->startTheGame();
        }
    }

    return false;
}



