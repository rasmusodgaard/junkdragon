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
    LoadMusic();
    PlayMusic();
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
    cough_s = Mix_LoadWAV("cough.wav");
    pick_up_s = Mix_LoadWAV("pick_up.wav");
    power_down_s = Mix_LoadWAV("powerdown.wav");
    
    
    mapOfSounds[breathe_fire] = *breathe_fire_s;
    mapOfSounds[cough] = *cough_s;
    mapOfSounds[pick_up] = *pick_up_s;
    mapOfSounds[power_down] = *power_down_s;
    
}

void AudioManager::LoadMusic(){
    currentMusic = Mix_LoadMUS("game_music.wav");
    if( currentMusic == nullptr)
    {
        std::cout << "Cannot load music"<< std::endl;
        return;
    }

}

void AudioManager::UnloadMusic(){
    Mix_FreeMusic(currentMusic);
}

void AudioManager::PlayMusic(){
    if( Mix_PlayingMusic() == 0 )
    {
        // Start the music
        Mix_PlayMusic( currentMusic, -1 );
    }
    
}

void AudioManager::PlaySound(soundKeys key){
    Mix_PlayChannel( -1, &mapOfSounds[key], 0 );
}


AudioManager::~AudioManager(){
    UnloadSoundChunks();
    UnloadMusic();
}
