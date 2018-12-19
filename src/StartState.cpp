//
//  StateState.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "JunkDragonGame.hpp"
#include "StartState.hpp"
#include "SpriteComponent.hpp"
#include "MenuOptionComponent.hpp"
#include <iostream>
#include <string>
#include "AudioManager.hpp"

void StartState::enterState() {
    std::cout << "START STATE" << std::endl;
    createCamera();

    spriteAtlas = sre::SpriteAtlas::create("junkdragon_title.json","junkdragon_title.png");

    optionObj = createGameObject();
    auto optionC = optionObj->addComponent<MenuOptionComponent>();
    optionC->name = "Play";

    // Place items to build the start screen scene
    backgroundComponent.init("background.png", {-1000.0f,-1000.0f},
        {2000.0f,2000.0f}, 25);

    createTitleSprite("title.png",      {0.0f,250.0f}, {2.0f,2.0f});
    createTitleSprite("bigdragon.png",  {-620.0f,-250.0f}, {1.0f,1.0f} );
    
    createTitleSprite("chilli.png",     {500.0f,-150.0f}, {1.5f,1.5f});
    createTitleSprite("pizza.png",      {630.0f,-200.0f}, {1.5f,1.5f});
    createTitleSprite("donut.png",      {500.0f,-400.0f}, {1.0f,1.0f});
    createTitleSprite("milk.png",       {650.0f,-400.0f}, {1.2f,1.2f});
    
    AudioManager::instance->LoadMusic();
    AudioManager::instance->PlayMusic();
}

// Tidy up
void StartState::exitState() {

    camera->unsetFollowObject();
    sceneObjects.erase( sceneObjects.begin(), sceneObjects.end() );
    
    optionObj = nullptr;
    spriteAtlas = nullptr;

    backgroundComponent.terminate();
}

void StartState::update( float time ) {
    if( optionObj->getComponent<MenuOptionComponent>()->play_pressed ) {
        JunkDragonGame::instance->startTheGame();
    }
}

// Create sprite for start screen
void StartState::createTitleSprite( std::string sprite_name, glm::vec2 pos, glm::vec2 scale) {
    auto title_obj = createGameObject();
    title_obj->setPosition( pos );
    auto title_objS = spriteAtlas->get( sprite_name );
    title_objS.setScale( scale );
    auto title_objSC = title_obj->addComponent<SpriteComponent>();
    title_objSC->setSprite(title_objS);
}

void StartState::render( sre::RenderPass &renderPass ) {
    
}

void StartState::createCamera( ) {
    // Camera Object
    camObj = std::shared_ptr<GameObject>(new GameObject());
    camera = camObj->addComponent<CameraFollow>();
    camera->setFollowObject(nullptr, {0,0});
}

bool StartState::onKey(SDL_Event &event) {
    if (event.key.keysym.sym == SDLK_SPACE) {
        if (event.type == SDL_KEYDOWN) {
            JunkDragonGame::instance->startTheGame();
        }
    }

    return false;
}



