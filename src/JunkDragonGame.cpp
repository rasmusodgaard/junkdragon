#include "JunkDragonGame.hpp"
#include <iostream>
#include "GameObject.hpp"
#include "sre/RenderPass.hpp"
#include "SpriteComponent.hpp"
#include <sre/Inspector.hpp>




const glm::vec2 JunkDragonGame::windowSize(400,600);
JunkDragonGame* JunkDragonGame::instance = nullptr;

JunkDragonGame::JunkDragonGame() {
    
    instance = this;
    
    r.setWindowSize(windowSize);
    r.init()
    .withSdlInitFlags(SDL_INIT_EVERYTHING)
    .withSdlWindowFlags(SDL_WINDOW_OPENGL);
    
    init();
    
    
    
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

void JunkDragonGame::init(){
    
    spriteAtlas = sre::SpriteAtlas::create("dragon.json","dragon.png");
    
    auto camObj = createGameObject();
    camera = camObj->addComponent<CameraFollow>();
    
    auto dragonObj = createGameObject();
    dragonObj->name = "Dragon";
    camera->setFollowObject(dragonObj, {0,0});
    auto spriteComponent = dragonObj->addComponent<SpriteComponent>();
    auto sprite = spriteAtlas->get("tile000.png");
    sprite.setScale({2,2});
    dragonObj->setPosition({200,200});
    spriteComponent->setSprite(sprite);
}

void JunkDragonGame::update(float time){
    
}

void JunkDragonGame::render() {
   
    
    auto rp = sre::RenderPass::create()
    .withCamera(camera->getCamera())
    .build();
    
    auto pos = camera->getGameObject()->getPosition();
    
    auto spriteBatchBuilder = sre::SpriteBatch::create();
    
    for (auto & go : sceneObjects){
        go->renderSprite(spriteBatchBuilder);
    }
    
    auto sb = spriteBatchBuilder.build();
    rp.draw(sb);
}

std::shared_ptr<GameObject> JunkDragonGame::createGameObject() {
    auto obj = std::shared_ptr<GameObject>(new GameObject());
    sceneObjects.push_back(obj);
    return obj;
}
