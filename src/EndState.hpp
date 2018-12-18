//
//  EndState.hpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once

#include "GameState.hpp"

class FloatTrackComponent;

class EndState : public GameState {
    public:
        void enterState() override;
        void exitState() override;
        void update(float time) override;
        void render( sre::RenderPass &renderPass ) override;
        bool onKey(SDL_Event &event) override;
        void createCamera() override;
        void recordScore( float final_score );
        void buildGUI();
        std::shared_ptr<GameObject> guiObj; 
        std::shared_ptr<FloatTrackComponent> high_score_comp;


    private:
        float new_score;
};