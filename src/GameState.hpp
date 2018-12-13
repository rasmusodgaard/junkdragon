//
//  GameState.hpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once

#include <string>

class GameState {
    public:
        virtual void enterState();
        virtual void exitState();
        virtual void update(float time);
        virtual void render();
        virtual bool onKey(SDL_Event &event);   
        std::string name = "_";
    private:
        

};