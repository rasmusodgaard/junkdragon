//
//  AudioManager.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 05/12/2018.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "SDL_mixer.h"



class AudioManager{
  
    
    
    
public:
    AudioManager();
    static AudioManager* instance;
    
    enum Sounds{
        breathe_fire,
        fireball_hit,
        house_burning
    };
    
    void playSound(Sounds);
    
   
private:
    
    std::vector<Mix_Chunk> sounds;
    Mix_Chunk *fireball_creation;

};
