//
//  Level.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//
#include <string>
#include <variant>
#include "glm/glm.hpp"
#include "sre/SpriteAtlas.hpp"

#pragma once

class JunkDragonGame;
class GameObject;

struct LevelValues{
    glm::vec2 starting_position;
    glm::vec2 wall_dimensions;
    std::vector<glm::vec2> house_positions;
    std::vector<glm::vec2> pick_up_positions;
    std::vector<std::string> pick_up_sprite;
};

class Level{
  
    
    
public:
    Level();
    
    
    void LoadLevel(std::string level);
    LevelValues GetLevelValues();
    //glm::vec2 GetStartingPosition();
    //glm::vec2 GetWallDimensions();
    //
    //std::vector<glm::vec2> GetHousePositions();
    //std::vector<glm::vec2> GetPickUpPositions();
private:
    LevelValues level_values;

    
    //glm::vec2 spawnPoint;
    //glm::vec2 wallDimensions;
    
    //std::vector<glm::vec2> housePositionVector;
    //std::vector<glm::vec2> pickUpPositionVector;
    //std::vector<std::string> pickUpSprites;
};


