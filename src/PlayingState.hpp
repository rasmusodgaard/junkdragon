//
//  PlayingState.hpp
//  SRE
//
//  Created by John O'Donnell
//


#pragma once

#include <string>
#include "GameState.hpp"

#define F_PHYSICS_TIMESTEP              0.3f

class PlayingState : public GameState {
    public:
        void enterState() override;
        void exitState() override;
        void update(float time) override;
        void render() override;
        bool onKey(SDL_Event &event) override;

        bool checkGameOver();

        std::string next_level_to_load = "_"; 
    private:
        bool burnination_has_begun;
        float time_elapsed;
        float time_remaining;
        float score;
        bool game_over;
};