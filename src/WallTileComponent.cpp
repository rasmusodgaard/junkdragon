//
//  WallTileComponent.cpp
//  SimpleRenderEngineProject
//
//  Created by Rasmus Odgaard on 18/12/2018.
//

#include "WallTileComponent.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "BackgroundComponent.hpp"
#include "JunkDragonGame.hpp"
#include <iostream>

WallTileComponent::WallTileComponent(GameObject *gameObject) : Component(gameObject){}


void WallTileComponent::renderWalls(sre::RenderPass &renderPass) {
    renderPass.draw(batch, glm::translate(glm::vec3(0, 0,0)));
}


void WallTileComponent::initWalls(std::string filename, glm::vec2 pos, glm::vec2 size, float wall_thickness){

    tex = sre::Texture::create().withFile(filename).build();
    auto atlas = sre::SpriteAtlas::createSingleSprite(tex, "wall", glm::vec2(0,0));
    auto sprite = atlas->get("wall");
    auto batchBuilder = sre::SpriteBatch::create();
    
    bool horizontal = (size.x >= size.y) ? true : false;
    
    float scale = (horizontal) ? size.y / tex->getHeight() : size.x / tex->getWidth();
    sprite.setScale({scale,scale});
    
    glm::vec2 start_pos = {pos.x - (size.x/2) - (wall_thickness/2), pos.y - (size.y/2)};
    sprite.setPosition(start_pos);
    batchBuilder.addSprite(sprite);
    
    
    int number_of_sprites = (horizontal) ? size.x / wall_thickness : size.y / wall_thickness;
    

    for (int i = 0; i<number_of_sprites; i++) {
        //glm::vec2 spritePos = (horizontal) ? glm::vec2(start_pos + tex->getWidth() * i * scale,0) : glm::vec2(0, start_pos * i * scale);
        //sprite.setPosition(spritePos);
        
        
        
        batchBuilder.addSprite(sprite);
    }

    

 // for (int i=0;i<resolution;i++){
 //     for (int j=0; j<resolution; j++) {
 //         sprite.setPosition(vec2(start_pos.x + tex->getWidth() * i * scale_x, start_pos.y + tex->getHeight() * j * scale_y) );
 //         batchBuilder.addSprite(sprite);
 //     }
 // }
    
    
  batch = batchBuilder.build();
}

void WallTileComponent::terminate() {
    tex.reset();
    batch.reset();
}
