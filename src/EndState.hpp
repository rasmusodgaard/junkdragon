//
//  EndState.hpp
//  SRE
//
//  Created by John O'Donnell
//

#include "GameState.hpp"

#pragma once

class EndState : public GameState {
    public:
        void enterState();
        void exitState();
        void update(float time);
        void render();
    private:
};