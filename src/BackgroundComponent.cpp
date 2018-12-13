//
//  BackgroundComponent.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include <sre/SpriteAtlas.hpp>
#include <sre/Texture.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "BackgroundComponent.hpp"
#include "JunkDragonGame.hpp"
#include <iostream>

using namespace sre;
using namespace glm;

BackgroundComponent::BackgroundComponent()
{

}

void BackgroundComponent::renderBackground(sre::RenderPass &renderPass, float offset) {
    renderPass.draw(batch, glm::translate(vec3(offset, 0,0)));
}

void BackgroundComponent::init(std::string filename, glm::vec2 start_pos, glm::vec2 size, float resolution) {
    tex = Texture::create().withFile(filename)
            .withFilterSampling(false)
            .build();

    auto atlas = SpriteAtlas::createSingleSprite(tex, "background", vec2(0,0));
    auto sprite = atlas->get("background");
    // float scale = JunkDragonGame::windowSize.y / tex->getHeight();
    float scale_x = size.x / (tex->getWidth() * resolution);
    float scale_y = size.y / (tex->getHeight()  * resolution);

    sprite.setScale({scale_x,scale_y});
    auto batchBuilder = SpriteBatch::create();

    for (int i=0;i<resolution;i++){
        for (int j=0; j<resolution; j++) {
            sprite.setPosition(start_pos.x + vec2(tex->getWidth() * i * scale_x, start_pos.y + tex->getHeight() * j * scale_y ));
            batchBuilder.addSprite(sprite);
        }
    }
    batch = batchBuilder.build();
}