#include "JunkDragonGame.hpp"
#include <iostream>
#include "GameObject.hpp"
#include "sre/RenderPass.hpp"


const glm::vec2 JunkDragonGame::windowSize(400,600);
JunkDragonGame* JunkDragonGame::instance = nullptr;

JunkDragonGame::JunkDragonGame() {
    
    instance = this;
    
    r.setWindowSize(windowSize);
    r.init()
    .withSdlInitFlags(SDL_INIT_EVERYTHING)
    .withSdlWindowFlags(SDL_WINDOW_OPENGL);
    
    //init();
    auto camObj = createGameObject();
    camera = camObj->addComponent<CameraFollow>();
    auto tempObj = createGameObject();
    
    //camera->setFollowObject(tempObj, {0,0});
    
    
    /*
    r.keyEvent = [&](SDL_Event& e){
        onKey(e);
    };
    */
    r.frameUpdate = [&](float deltaTime){
       update(deltaTime);
    };
    r.frameRender = [&](){
        render();    };
    // start game loop
    r.startEventLoop();
    
    
}

void JunkDragonGame::update(float time){
    
}

void JunkDragonGame::render() {
   
    
    auto rp = sre::RenderPass::create()
    .withCamera(camera->getCamera())
    .build();
    
    auto pos = camera->getGameObject()->getPosition();
    
    auto spriteBatchBuilder = sre::SpriteBatch::create();
    
}

std::shared_ptr<GameObject> JunkDragonGame::createGameObject() {
    auto obj = std::shared_ptr<GameObject>(new GameObject());
    sceneObjects.push_back(obj);
    return obj;
}
