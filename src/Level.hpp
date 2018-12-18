//
//  Level.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//
#pragma once


#include <string>
#include "glm/glm.hpp"
#include "sre/SpriteAtlas.hpp"


class JunkDragonGame;
class GameObject;
class Command;

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
private:
    LevelValues level_values;
};


