//
//  Level.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//
#include <string>
#include "glm/glm.hpp"
#include "sre/SpriteAtlas.hpp"

#pragma once

class JunkDragonGame;
class GameObject;

class Level{
  
public:
    void GenerateLevel();

    glm::vec2 GetStartingPosition();
private:
    glm::vec2 spawnPoint;

};


