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





//load level
void Level::GenerateLevel(){
    
    std::ifstream fis("level0.json");
    
    rapidjson::IStreamWrapper isw(fis);
    rapidjson::Document d;
    d.ParseStream(isw);

    const rapidjson::Value& spawn = d["spawn"];
    //const rapidjson::Value& b = d["housePlacement"];
    
    //Get spawnpoint in level
    spawnPoint.x = spawn["x"].GetInt();
    spawnPoint.y = spawn["y"].GetInt();
    
    
    
/*
    for (rapidjson::SizeType i = 0; i < b.Size(); i++)
    {
        const rapidjson::Value& c = b[i];
        std::vector<int> valTemp;
        
        for (rapidjson::SizeType j = 0; j < c.Size(); j++) {
            valTemp.push_back(c[j].GetInt());
        }
        //values.push_back(valTemp);
    }

    startingPosition.x = spawn["x"].GetFloat();
    startingPosition.y = spawn["y"].GetFloat();
    startingRotation = spawn["angle"].GetFloat();

    for (int i = 0; i<4; i++) {
        floorColor[i] = d["floorColor"][i].GetFloat();
        ceilColor[i] = d["ceilColor"][i].GetFloat();
    }
    
    */
     
}

glm::vec2 Level::GetStartingPosition(){
    return spawnPoint;
}

//init level

//Create house

//Set Background

//
