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
    for (int i = 0; i < sounds.size(); i++){
        Mix_FreeChunk(&sounds[i]);
    }
}

void AudioManager::LoadSoundChunks(){
    
    breathe_fire_s = Mix_LoadWAV( "breathe_fire.wav" );
    
    if(breathe_fire_s == nullptr){
        std::cout << "breathe_fire sound was not loaded" << std::endl;
    }
    
    sounds.push_back(*breathe_fire_s);
    
    
}

void AudioManager::playSound(SoundsEnum){
    Mix_PlayChannel( -1, &sounds[breathe_fire], 0 );
}


AudioManager::~AudioManager(){
    UnloadSoundChunks();
}
