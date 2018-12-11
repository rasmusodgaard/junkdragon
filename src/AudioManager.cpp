//
//  AudioManager.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 05/12/2018.
//

#include "AudioManager.hpp"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager(){
    instance = this;
    
    
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        std::cout << "Cannot initialize audio output"<< std::endl;
        return;
    }
    
    LoadSoundChunks();
}

void AudioManager::UnloadSoundChunks(){
    std::map<soundKeys, Mix_Chunk>::iterator it;
    
    for ( it = mapOfSounds.begin(); it != mapOfSounds.end(); it++ )
    {
        Mix_FreeChunk(&it->second);
    }
    mapOfSounds.clear();
}

void AudioManager::LoadSoundChunks(){
    
    breathe_fire_s = Mix_LoadWAV( "breathe_fire.wav" );
    
    if(breathe_fire_s == nullptr){
        std::cout << "breathe_fire sound was not loaded" << std::endl;
    }
    
    mapOfSounds[breathe_fire] = *breathe_fire_s;
    
}

void AudioManager::playSound(soundKeys key){
    Mix_PlayChannel( -1, &mapOfSounds[key], 0 );
}


AudioManager::~AudioManager(){
    UnloadSoundChunks();
}
