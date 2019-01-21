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

bool BackgroundComponent::getIsLoaded() {
    return isLoaded;
}

void BackgroundComponent::init(std::string filename) {
    tex = Texture::create().withFile(filename)
            .withFilterSampling(false)
            .build();

    // Create atlas for background png
    atlas = SpriteAtlas::createSingleSprite(tex, "background", vec2(0,0));
    sprite = atlas->get("background");

    // No need to init this background component again
    isLoaded = true;
}

void BackgroundComponent::buildBackground(glm::vec2 start_pos, glm::vec2 size, float resolution) {
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

void BackgroundComponent::buildBackground(glm::vec2 start_pos, glm::vec2 size, float resolution, int thickness) {
    // Scale factor is dependant on area to cover, texture width and resolution
    float scale_x = (size.x-thickness*2)/ (tex->getWidth() * resolution);
    float scale_y = size.y / (tex->getHeight()  * resolution);

    sprite.setScale({scale_x,scale_y});
    auto batchBuilder = SpriteBatch::create();

    // Tile the area according to the size and resolution
    for (int i=0;i<resolution;i++){
        for (int j=0; j<resolution; j++) {
            sprite.setPosition(vec2(start_pos.x + thickness + tex->getWidth() * i * scale_x, 
                                start_pos.y + tex->getHeight() * j * scale_y) );
            batchBuilder.addSprite(sprite);
        }
    }
    batch = batchBuilder.build();
}

// Remove reference to shared_ptrs, freeing memory (if no other references exist)
void BackgroundComponent::terminate() {
    // tex.reset(); does not work
    batch.reset();
}
