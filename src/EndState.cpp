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
    JunkDragonGame::instance->dragonObj->getComponent<DragonController>()->stop();
}

void EndState::exitState() {
    
}

void EndState::update( float time ) {
    
}

void EndState::render() {
    
}