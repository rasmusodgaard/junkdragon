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
#include "SpriteComponent.hpp"

void TransitionState::enterState() {
    std::cout << "TRANSITION STATE" << std::endl;
    createCamera();

    optionObj = createGameObject();
    auto optionC = optionObj->addComponent<MenuOptionComponent>();
    optionC->name = "Next";

    if(!isLoaded){
        spriteAtlas = sre::SpriteAtlas::create("junkdragon_transition.json","junkdragon_transition.png");
        isLoaded = true;
    }
    
    // Place items to build the start screen scene
    if( !backgroundComponent.getIsLoaded() ) {
        backgroundComponent.init("background.png");
    }
    backgroundComponent.buildBackground({-1000.0f,-1000.0f}, {2000.0f,2000.0f}, 1);
    
    auto transition_obj = createGameObject();
    transition_obj->setPosition( {0.0f, 300.0f} );
    auto transition_objS = spriteAtlas->get("press_enter.png");
    transition_objS.setScale( {2.0f,2.0f} );
    auto transition_objSC = transition_obj->addComponent<SpriteComponent>();
    transition_objSC->setSprite(transition_objS);
}

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



