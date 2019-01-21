//
//  Level.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//

#include "Level.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>
#include "JunkDragonGame.hpp"



//needs assertion or check for relevance! Menu will not have the same objects.

Level::Level(){
    
}


//load level
void Level::LoadLevel(std::string level){
    
    
    
    std::ifstream fis(level);
    
    rapidjson::IStreamWrapper isw(fis);
    rapidjson::Document d;
    d.ParseStream(isw);

    const rapidjson::Value& spawn = d["spawn"];
    const rapidjson::Value& dimensions = d["dimensions"];
    
    const rapidjson::Value& housePosX = d["housePositionsX"];
    const rapidjson::Value& housePosY = d["housePositionsY"];
    
    const rapidjson::Value& pickUpPosX = d["pickUpPositionX"];
    const rapidjson::Value& pickUpPosY = d["pickUpPositionY"];
    const rapidjson::Value& pickUpSprites = d["pickUpSprites"];
    
    const rapidjson::Value& time = d["time"];
    
    //Get spawnpoint in level
    level_values.starting_position.x = spawn["x"].GetInt();
    level_values.starting_position.y = spawn["y"].GetInt();
    
    //Get surrounding wall dimensions
    level_values.wall_dimensions.x = dimensions["x"].GetInt();
    level_values.wall_dimensions.y = dimensions["y"].GetInt();
    
    level_values.time = (float)time.GetDouble();
    
    for (rapidjson::SizeType i = 0; i < housePosX.Size(); i++)
    {
        level_values.house_positions.push_back({housePosX[i].GetInt(),housePosY[i].GetInt()});
    }
    
    for (rapidjson::SizeType i = 0; i < pickUpPosX.Size(); i++)
    {
        level_values.pick_up_positions.push_back({pickUpPosX[i].GetInt(),pickUpPosY[i].GetInt()});
        level_values.pick_up_sprite.push_back(pickUpSprites[i].GetString());
    } 
}

LevelValues Level::GetLevelValues(){
    return level_values;
}




