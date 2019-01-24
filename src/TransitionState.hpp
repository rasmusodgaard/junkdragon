//
//  TransitionState.hpp
//  SRE
//

#pragma once

#include "GameState.hpp"

class MenuOptionComponent;

class TransitionState : public GameState {
    public:
        void enterState() override;
        void exitState() override;
        void update(float time) override;
        void render( sre::RenderPass &renderPass ) override;
        bool onKey(SDL_Event &event) override;
        void createCamera() override;

    private:
        std::shared_ptr<GameObject> optionObj;
        std::shared_ptr<MenuOptionComponent> optionC;
};