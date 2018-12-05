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
    
    
    
    fireball_creation = Mix_LoadWAV( "Explosion1.wav" );
    
    sounds.push_back(*fireball_creation);
    
}

void AudioManager::playSound(Sounds){
    Mix_PlayChannel( -1, &sounds[breathe_fire], 0 );
}
