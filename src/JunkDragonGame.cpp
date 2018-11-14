#include "JunkDragonGame.hpp"
#include <iostream>
#include "GameObject.hpp"
#include "sre/RenderPass.hpp"
#include "SpriteComponent.hpp"
#include "SpriteAnimationComponent.hpp"
#include <sre/Inspector.hpp>
#include "DragonController.hpp"
#include "FireBallController.hpp"


const glm::vec2 JunkDragonGame::windowSize(400,600);
JunkDragonGame* JunkDragonGame::instance = nullptr;

JunkDragonGame::JunkDragonGame() {
    
    instance = this;
    
    r.setWindowSize(windowSize);
    r.init()
    .withSdlInitFlags(SDL_INIT_EVERYTHING)
    .withSdlWindowFlags(SDL_WINDOW_OPENGL);
    
    init();
    
    r.keyEvent = [&](SDL_Event& e){
        onKey(e);
    };
    
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
    
    // Dragon Game Object (Player)
    dragonObj = createGameObject();
    dragonObj->name = "Dragon";
    camera->setFollowObject(dragonObj, {0,0});
    dragonObj->setPosition({0,0});
    dragonObj->setRotation(0.0f);
    // Add controller
    auto dragonC = dragonObj->addComponent<DragonController>();
    //dragonC->setFireballCreator( createFireBall() );
    // Add sprite component
    auto sprite = spriteAtlas->get("tile009.png");
    sprite.setScale({2,2}); 
    auto spriteC = dragonObj->addComponent<SpriteComponent>();
    spriteC->setSprite(sprite);
    // Add animatinos
    auto animC = dragonObj->addComponent<SpriteAnimationComponent>();
    animC->setSprites({spriteAtlas->get("tile009.png"), spriteAtlas->get("tile010.png"), spriteAtlas->get("tile011.png")});
    animC->setScale({2,2});

    // Add background
    backgroundComponent.init("background.png");
}

void JunkDragonGame::update(float time){
    for (int i=0;i<sceneObjects.size();i++){
        sceneObjects[i]->update(time);
        if (sceneObjects[i]->getDeleteMe()) {
            sceneObjects.erase(sceneObjects.begin() + i);
        }
    }
}

void JunkDragonGame::render() {
    auto rp = sre::RenderPass::create()
    .withCamera(camera->getCamera())
    .build();
    
    auto pos = camera->getGameObject()->getPosition();
    backgroundComponent.renderBackground(rp,0.0f);
    
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

void JunkDragonGame::onKey(SDL_Event &event) {
    for (auto & gameObject: sceneObjects) {
        for (auto & c : gameObject->getComponents()){
            bool consumed = c->onKey(event);
            if (consumed){
                return;
            }
        }
    }
}

void JunkDragonGame::createFireBall( ) {
    auto fireballObj = createGameObject();
    fireballObj->setPosition( dragonObj->getPosition() );
    fireballObj->setRotation( dragonObj->getRotation() );
    auto fireballController = fireballObj->addComponent<FireBallController>();
    fireballController->setVelocity( dragonObj->getRotation() );
    auto fireballSprite = spriteAtlas->get("tile009.png");
    fireballSprite.setScale({1,1});
    auto fireballSpriteComponent = fireballObj->addComponent<SpriteComponent>();
    fireballSpriteComponent->setSprite(fireballSprite);
}