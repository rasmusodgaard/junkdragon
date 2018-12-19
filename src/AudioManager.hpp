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
        cough,
        pick_up,
        power_down
    };

    
    void PlaySound(soundKeys key);
    void PlayMusic();
    // Load/unload all audio
    void LoadSoundChunks();
    void UnloadSoundChunks();
    void LoadMusic();
    void UnloadMusic();
   
    // Map enumerator to audio samples
    std::map <soundKeys, Mix_Chunk> mapOfSounds;
private:
   
    // Sound effects
    Mix_Chunk *breathe_fire_s;
    Mix_Chunk *pick_up_s;
    Mix_Chunk *power_down_s;
    Mix_Chunk *cough_s;
    
    Mix_Music *currentMusic;
};
