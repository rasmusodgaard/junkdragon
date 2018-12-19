//
//  BackgroundComponent.cpp
//  SRE
//
//  Created by John O'Donnell
//

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
    // Render the batch that was prepared in init
    renderPass.draw(batch, glm::translate(vec3(offset, 0,0)));
}

void BackgroundComponent::init(std::string filename, glm::vec2 start_pos, glm::vec2 size, float resolution) {
    tex = Texture::create().withFile(filename)
            .withFilterSampling(false)
            .build();

    // Create atlas for background png
    auto atlas = SpriteAtlas::createSingleSprite(tex, "background", vec2(0,0));
    auto sprite = atlas->get("background");
    
    // Scale factor is dependant on area to cover, texture width and resolution
    float scale_x = size.x / (tex->getWidth() * resolution);
    float scale_y = size.y / (tex->getHeight()  * resolution);

    sprite.setScale({scale_x,scale_y});
    auto batchBuilder = SpriteBatch::create();

    // Tile the area according to the size and resolution
    for (int i=0;i<resolution;i++){
        for (int j=0; j<resolution; j++) {
            sprite.setPosition(vec2(start_pos.x + tex->getWidth() * i * scale_x, 
                                start_pos.y + tex->getHeight() * j * scale_y) );
            batchBuilder.addSprite(sprite);
        }
    }
    batch = batchBuilder.build();
}

// Remove reference to shared_ptrs, freeing memory (if not other references exist)
void BackgroundComponent::terminate() {
    tex.reset();
    batch.reset();
}