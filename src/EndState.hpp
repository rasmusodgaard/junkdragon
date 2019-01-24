//
//  EndState.hpp
//  SRE
//

#pragma once

#include "GameState.hpp"
#include <iostream>

class SingleVarGuiComponent;

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
        std::shared_ptr<SingleVarGuiComponent> high_score_comp;
        void setEndMessage(std::string msg_filename);

    private:
        int new_score = 0.0f;

        std::string end_msg_filename;

        std::shared_ptr<sre::SpriteAtlas> spriteAtlas;

        std::shared_ptr<GameObject> optionObj;
        std::shared_ptr<MenuOptionComponent> optionC;
};