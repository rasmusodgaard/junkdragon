//
//  PlayingState.hpp
//  SRE
//
//  Created by John O'Donnell
//

#include "GameState.hpp"

#pragma once

class PlayingState : public GameState {
    public:
        void enterState();
        void exitState();
        void update(float time);
        void render();
    private:
};