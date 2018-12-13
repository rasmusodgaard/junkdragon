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
}

void StartState::exitState() {
    
}

void StartState::update( float time ) {
    
}

void StartState::render() {
    
}

bool StartState::onKey(SDL_Event &event) {

    if (event.key.keysym.sym == SDLK_SPACE) {
        if (event.type == SDL_KEYDOWN) {
            std::cout << "SPACE PRESSED" << std::endl;
            JunkDragonGame::instance->startTheGame();
        }
    }

    return false;
}



