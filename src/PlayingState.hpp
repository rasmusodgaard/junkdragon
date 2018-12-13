//
//  PlayingState.hpp
//  SRE
//
//  Created by John O'Donnell
//


#pragma once

#include "GameState.hpp"

#define F_PHYSICS_TIMESTEP              0.3f

class PlayingState : public GameState {
    public:
        void enterState();
        void exitState();
        void update(float time);
        void render();
    private:
};