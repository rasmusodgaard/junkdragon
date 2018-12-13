//
//  GameState.hpp
//  SRE
//
//  Created by John O'Donnell
//
#include <string>

#pragma once

class GameState {
    public:
        virtual void enterState();
        virtual void exitState();
        virtual void update(float time);
        virtual void render();

        std::string name = "_";
    private:
        

};