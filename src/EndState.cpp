//
//  EndState.cpp
//  SRE
//

#include "JunkDragonGame.hpp"
#include "AudioManager.hpp"
#include "MenuOptionComponent.hpp"
#include "EndState.hpp"
#include "SpriteComponent.hpp"
#include <iostream>

void EndState::enterState() {
    std::cout << "END STATE" << std::endl;
    createCamera();
    buildGUI();

    if(!isLoaded){
        spriteAtlas = sre::SpriteAtlas::create("junkdragon_endgame.json","junkdragon_endgame.png");
        isLoaded = true;
    }
    
    auto gameover_obj = createGameObject();
    gameover_obj->setPosition( {0.0f, 300.0f} );
    auto gameover_objS = spriteAtlas->get( "gameover.png" );
    gameover_objS.setScale( {2.0f,2.0f} );
    auto gameover_objSC = gameover_obj->addComponent<SpriteComponent>();
    gameover_objSC->setSprite(gameover_objS);

    high_score_comp = guiObj->addComponent<SingleVarGuiComponent>();
    high_score_comp->init( "High score:", new_score, {0.35f, 0.45f}, {0.3f,0.1f} );

    if( !backgroundComponent.getIsLoaded() ){
        backgroundComponent.init("background.png");
    }
    backgroundComponent.buildBackground({-1000.0f,-1000.0f},{2000.0f,2000.0f}, 25);

    optionObj = createGameObject();
    auto optionC = optionObj->addComponent<MenuOptionComponent>();
    optionC->name = "Play";
}

void EndState::exitState() {
    guiObj->removeComponent(high_score_comp);
    high_score_comp = nullptr;
    guiObj          = nullptr;
    camera->unsetFollowObject();

    backgroundComponent.terminate();

    sceneObjects.erase(sceneObjects.begin(), sceneObjects.end());
}

void EndState::update( float time ) {
    if( optionObj->getComponent<MenuOptionComponent>()->play_pressed ) {
        JunkDragonGame::instance->startTheGame();
    }
}

void EndState::render( sre::RenderPass &renderPass ) {

}

void EndState::createCamera( ) {
    // Camera Object
    camObj = std::shared_ptr<GameObject>(new GameObject());
    camera = camObj->addComponent<CameraFollow>();
    camera->setFollowObject(nullptr, {0,0});
}

bool EndState::onKey(SDL_Event &event) {
    return false;
}

void EndState::recordScore( float final_score ) {
    new_score = final_score;
}

void EndState::buildGUI() {

    guiObj = createGameObject();

}
