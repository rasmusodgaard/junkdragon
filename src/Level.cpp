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

//load level
void Level::LoadLevel(std::string level){
    
    std::ifstream fis("level1.json");
    
    rapidjson::IStreamWrapper isw(fis);
    rapidjson::Document d;
    d.ParseStream(isw);

    const rapidjson::Value& spawn = d["spawn"];
    const rapidjson::Value& dimensions = d["dimensions"];
    const rapidjson::Value& hpX = d["housePositionsX"];
    const rapidjson::Value& hpY = d["housePositionsY"];
    
    //Get spawnpoint in level
    spawnPoint.x = spawn["x"].GetInt();
    spawnPoint.y = spawn["y"].GetInt();
    
    //Get surrounding wall dimensions
    wallDimensions.x = dimensions["x"].GetInt();
    wallDimensions.y = dimensions["y"].GetInt();
    
    for (rapidjson::SizeType i = 0; i < hpX.Size(); i++)
    {
        int tempX = hpX[i].GetInt();
        int tempY = hpY[i].GetInt();
        housePositions.push_back({tempX,tempY});
    }
}

glm::vec2 Level::GetStartingPosition(){
    return spawnPoint;
}

std::vector<glm::vec2> Level::GetHousePositions(){
    return housePositions;
}

glm::vec2 Level::GetWallDimensions(){
    return wallDimensions;
}

//init level

//Set Background

//
