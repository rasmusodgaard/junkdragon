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
    
    // enum keys for map mapOfSounds
    enum soundKeys{
        breathe_fire,
        house_burning
    };
    
    void playSound(soundKeys key);
    
    // Load all sound effects (Chunks)
    void LoadSoundChunks();
    
    // Unload all sound effects (Chunks)
    void UnloadSoundChunks();
   
    std::map <soundKeys, Mix_Chunk> mapOfSounds;
private:
   
    //std::vector<Mix_Chunk> sounds;
    Mix_Chunk *breathe_fire_s;

};
