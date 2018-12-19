//
//  WallTileComponent.hpp
//  SimpleRenderEngineProject
//
//  Created by Rasmus Odgaard on 18/12/2018.
//
#pragma once

#define WallTileComponent_hpp
#include <stdio.h>
#include "Component.hpp"
#include "sre/SpriteBatch.hpp"
#include "sre/Texture.hpp"
#include "sre/RenderPass.hpp"

class WallTileComponent: public Component{

public:
    WallTileComponent(GameObject *gameObject);
    void renderWalls(sre::RenderPass &renderPass);
    void initWalls (std::string filename, glm::vec2 pos, glm::vec2 size, float wall_thickness);
    void terminate();
private:
    std::shared_ptr<sre::Texture> tex;
    std::shared_ptr<sre::SpriteBatch> batch;

};
