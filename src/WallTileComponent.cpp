//
//  WallTileComponent.cpp
//  SimpleRenderEngineProject
//
//  Created by Rasmus Odgaard on 18/12/2018.
//

#include "WallTileComponent.hpp"

//tex = sre::Texture::create().withFile("wall.png").build();
//auto atlas = sre::SpriteAtlas::createSingleSprite(tex, "wall", //glm::vec2(0,0));
//auto sprite = atlas->get("wall");
//
//  for (int i = 0; i<4; i++) {
//      float scale_x = size.x / (tex->getWidth() * 1);
//      float scale_y = size.y / (tex->getHeight()  * 1);
//      sprite.setScale({scale_x,scale_y});
//  }
//
//
//
//  auto batchBuilder = SpriteBatch::create();
//
//  for (int i=0;i<resolution;i++){
//      for (int j=0; j<resolution; j++) {
//          sprite.setPosition(vec2(start_pos.x + tex->getWidth() * i * scale_x,
//                                  start_pos.y + tex->getHeight() * j * scale_y) );
//          batchBuilder.addSprite(sprite);
//      }
//  }
//  batch = batchBuilder.build();
