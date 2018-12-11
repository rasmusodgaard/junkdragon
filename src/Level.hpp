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
    void LoadLevel(std::string level);
    std::vector<glm::vec2> GetHousePositions();
    glm::vec2 GetStartingPosition();
    glm::vec2 GetWallDimensions();
private:
    glm::vec2 spawnPoint;
    glm::vec2 wallDimensions;
    std::vector<glm::vec2> housePositions;
};


