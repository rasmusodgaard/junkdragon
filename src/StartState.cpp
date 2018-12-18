//
//  StateState.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "JunkDragonGame.hpp"
#include "StartState.hpp"
#include "MenuOptionComponent.hpp"
#include <iostream>

void StartState::enterState() {
    std::cout << "START STATE" << std::endl;
    createCamera();

    optionObj = createGameObject();
    auto optionC = optionObj->addComponent<MenuOptionComponent>();
    optionC->name = "Option1";

}

void StartState::exitState() {
    optionObj = nullptr;
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

    if (event.key.keysym.sym == SDLK_LEFT) {
        if (event.type == SDL_KEYDOWN) {
            // current_choice = option1;
        }
    }

    if (event.key.keysym.sym == SDLK_RIGHT) {
        if (event.type == SDL_KEYDOWN) {
            // current_choice = option2;
        }
    }

    return false;
}



