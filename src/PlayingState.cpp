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

void PlayingState::enterState() {
    std::cout << "PLAYING STATE" << std::endl;
}

void PlayingState::exitState() {
    
}

void PlayingState::update( float time ) {
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

void PlayingState::render() {
    
}


