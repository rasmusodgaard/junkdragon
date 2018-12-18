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

class WallTileComponent{

public:
    

    
private:
    std::shared_ptr<sre::Texture> tex;
    std::shared_ptr<sre::SpriteBatch> batch;

};
