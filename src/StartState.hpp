//
//  StartState.hpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once

#include "GameState.hpp"
#include "sre/SpriteAtlas.hpp"
#define INT_BACKGROUND_RESOLUTION      50


class MenuOptionComponent;

class StartState : public GameState {
    public:
        void enterState() override;
        void exitState() override;
        void update(float time) override;
        void render( sre::RenderPass &renderPass ) override;
        bool onKey(SDL_Event &event) override;
        void createCamera() override;
        void createTitleSprite( std::string sprite_name, glm::vec2 pos, glm::vec2 scale );

    private:
        std::shared_ptr<sre::SpriteAtlas> spriteAtlas;

        std::shared_ptr<GameObject> optionObj;
        std::shared_ptr<MenuOptionComponent> optionC;
};