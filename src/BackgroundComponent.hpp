//
//  BackgroundComponent.hpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once

#include "Component.hpp"
#include "sre/SpriteBatch.hpp"
#include "sre/Texture.hpp"
#include "sre/RenderPass.hpp"

class BackgroundComponent {
    public:
        BackgroundComponent();
        void init(std::string filename);
        void buildBackground(glm::vec2 start_pos, glm::vec2 size, float resolution);
        void terminate();
        void renderBackground(sre::RenderPass& renderPass, float offset);
        bool getIsLoaded();
    private:
        std::shared_ptr<sre::Texture> tex;
        std::shared_ptr<sre::SpriteBatch> batch;
        std::shared_ptr<sre::SpriteAtlas> atlas;
        sre::Sprite sprite;
        bool isLoaded = false;

};