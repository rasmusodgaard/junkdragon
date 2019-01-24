//
//  StateState.cpp
//  SRE
//

#include "JunkDragonGame.hpp"
#include "TransitionState.hpp"
#include "MenuOptionComponent.hpp"
#include <iostream>
#include <string>
#include "AudioManager.hpp"

void TransitionState::enterState() {
    std::cout << "TRANSITION STATE" << std::endl;
    createCamera();

    optionObj = createGameObject();
    auto optionC = optionObj->addComponent<MenuOptionComponent>();
    optionC->name = "Next";

    // Place items to build the start screen scene
    if( !backgroundComponent.getIsLoaded() ) {
        backgroundComponent.init("black_background.png");
    }
    backgroundComponent.buildBackground({-1000.0f,-1000.0f}, {2000.0f,2000.0f}, 1);
    
    if (!Mix_PlayingMusic()) {
        AudioManager::instance->PlayMusic();
    }
}

// Tidy up
void TransitionState::exitState() {

    camera->unsetFollowObject();
    sceneObjects.erase( sceneObjects.begin(), sceneObjects.end() );
    
    optionObj = nullptr;

    backgroundComponent.terminate();
}

void TransitionState::update( float time ) {
    if( optionObj->getComponent<MenuOptionComponent>()->play_pressed ) {
        JunkDragonGame::instance->startTheGame();
    }
}

void TransitionState::render( sre::RenderPass &renderPass ) {
    
}

void TransitionState::createCamera( ) {
    // Camera Object
    camObj = std::shared_ptr<GameObject>(new GameObject());
    camera = camObj->addComponent<CameraFollow>();
    camera->setFollowObject(nullptr, {0,0});
}

bool TransitionState::onKey(SDL_Event &event) {
    return false;
}



