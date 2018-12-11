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
        pick_up
    };
    
    void playSound(soundKeys key);
    
    // Load/unload all audio
    void LoadSoundChunks();
    void UnloadSoundChunks();
    void LoadMusic();
    void UnloadMusic();
   
    std::map <soundKeys, Mix_Chunk> mapOfSounds;
private:
   
    // Sound effects
    Mix_Chunk *breathe_fire_s;
    Mix_Chunk *pick_up_s;
    Mix_Music *music;
};
