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

    score                   = 0.0f;
    burnination_has_begun   = false;
    time_elapsed            = 0.0f;
    time_remaining          = 10.0f;
    game_over               = false;
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

    if( !game_over && checkGameOver() ) {
            game_over = true;
            JunkDragonGame::instance->endTheGame();
    } else {
        time_remaining = fmax(time_remaining - time, 0.0f);
    }
    
}

void PlayingState::render() {
    
}

bool PlayingState::checkGameOver() {
    if (JunkDragonGame::instance->n_houses == 0) {
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

