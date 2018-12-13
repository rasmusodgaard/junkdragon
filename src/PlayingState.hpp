//
//  PlayingState.hpp
//  SRE
//
//  Created by John O'Donnell
//


#pragma once

#include <string>
#include "GameState.hpp"
#include "Level.hpp"

#define F_PHYSICS_TIMESTEP              0.3f
#define INT_WALL_THICKNESS             50


class PlayingState : public GameState {
    public:
        void enterState() override;
        void exitState() override;
        void update(float time) override;
        void render() override;
        bool onKey(SDL_Event &event) override;
        void setNextLevelToLoad(std::string next_level);

        bool checkGameOver();

        std::string next_level_to_load = "_"; 
    private:
        std::shared_ptr<Level> current_level;
        bool burnination_has_begun;
        float time_elapsed;
        float time_remaining;
        float score;
        bool game_over;
};