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
        void enterState() override;
        void exitState() override;
        void update(float time) override;
        void render() override;
        bool onKey(SDL_Event &event) override;
        void createCamera() override;


    private:
};