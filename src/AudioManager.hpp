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
#include <map>

#include "SDL_mixer.h"



class AudioManager{
  
    
    
    
public:
    AudioManager();
    ~AudioManager();
    static AudioManager* instance;
    
    enum SoundsEnum{
        breathe_fire,
        fireball_hit,
        house_burning
    };
    
    void playSound(SoundsEnum);
    
    // Load all sound effects (Chunks)
    void LoadSoundChunks();
    
    // Unload all sound effects (Chunks)
    void UnloadSoundChunks();
   
private:
   
    std::vector<Mix_Chunk> sounds;
    Mix_Chunk *breathe_fire_s;

};
