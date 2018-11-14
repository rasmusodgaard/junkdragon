#include "JunkDragonGame.hpp"
#include <iostream>
#include "GameObject.hpp"
#include "sre/RenderPass.hpp"
#include "SpriteComponent.hpp"
#include "SpriteAnimationComponent.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "PhysicsComponent.hpp"
#include <sre/Inspector.hpp>
#include "DragonController.hpp"
#include "FireBallController.hpp"
#include "BurnableComponent.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

const glm::vec2 JunkDragonGame::windowSize(800,600);
JunkDragonGame* JunkDragonGame::instance = nullptr;

JunkDragonGame::JunkDragonGame():debugDraw(physicsScale) {
    
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
    initPhysics();
    
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
    
    auto HouseObj = createGameObject();
    HouseObj->setPosition({200,200});
    HouseObj->setRotation(0.0f);
    auto houseSprite = spriteAtlas->get("tile003.png");
    auto houseSpriteC = HouseObj->addComponent<SpriteComponent>();
    houseSpriteC->setSprite(houseSprite);
    HouseObj->addComponent<BurnableComponent>();
    
    auto HousePhysics = HouseObj->addComponent<PhysicsComponent>();
    HousePhysics->initCircle(b2_staticBody, 100/physicsScale, HouseObj->getPosition()/physicsScale, HouseObj->getRotation(), 1);
    HousePhysics->setSensor(true);
}

void JunkDragonGame::update(float time){
    updatePhysics();
    if (time > 0.03) // if framerate approx 30 fps then run two physics steps
	{
		updatePhysics();
	}

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

    // if (doDebugDraw){
    //     static sre::Inspector profiler;
    //     profiler.update();
    //     profiler.gui(false);
    // }
    
    auto pos = camera->getGameObject()->getPosition();
    backgroundComponent.renderBackground(rp,0.0f);
    
    auto spriteBatchBuilder = sre::SpriteBatch::create();
    
    for (auto & go : sceneObjects){
        go->renderSprite(spriteBatchBuilder);
    }
    
    auto sb = spriteBatchBuilder.build();
    rp.draw(sb);

    if (doDebugDraw){
        world->DrawDebugData();
        rp.drawLines(debugDraw.getLines());
        debugDraw.clear();
    }
}


void JunkDragonGame::updatePhysics() {
    const int positionIterations = 4;
    const int velocityIterations = 12;
    world->Step(timeStep, velocityIterations, positionIterations);

    for (auto phys : physicsComponentLookup) {
        PhysicsComponent* physicsComponent = phys.second;
        if (physicsComponent->isAutoUpdate() == false) continue;
        auto position = physicsComponent->getBody()->GetPosition();
        float angle = physicsComponent->getBody()->GetAngle();
        auto gameObject = physicsComponent->getGameObject();
        gameObject->setPosition(glm::vec2(position.x*physicsScale, position.y*physicsScale));
        gameObject->setRotation(angle);
    }
}

void JunkDragonGame::initPhysics() {
    float gravity = 0.0f; // 0.0 m/s2
    delete world;
    world = new b2World(b2Vec2(0,gravity));
    world->SetContactListener(this);

    if (doDebugDraw){
        world->SetDebugDraw(&debugDraw);
    }
}

void JunkDragonGame::BeginContact(b2Contact *contact) {
    b2ContactListener::BeginContact(contact);
    handleContact(contact, true);
}

void JunkDragonGame::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
    handleContact(contact, false);
}

void JunkDragonGame::handleContact(b2Contact *contact, bool begin) {
    std::cout << "Begin contact" << std::endl;

    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
    auto physA = physicsComponentLookup.find(fixA);
    auto physB = physicsComponentLookup.find(fixB);
    if (physA !=physicsComponentLookup.end() && physB != physicsComponentLookup.end()){
        auto & aComponents = physA->second->getGameObject()->getComponents();
        auto & bComponents = physB->second->getGameObject()->getComponents();
        for (auto & c : aComponents){
            if (begin){
                c->onCollisionStart(physB->second);
            } else {
                c->onCollisionEnd(physB->second);
            }
        }
        for (auto & c : bComponents){
            if (begin){
                c->onCollisionStart(physA->second);
            } else {
                c->onCollisionEnd(physA->second);
            }
        }
    }
}

void JunkDragonGame::registerPhysicsComponent(PhysicsComponent *r) {
    physicsComponentLookup[r->getFixture()] = r;
}

void JunkDragonGame::deregisterPhysicsComponent(PhysicsComponent *r) {
    auto iter = physicsComponentLookup.find(r->getFixture());
    if (iter != physicsComponentLookup.end()){
        physicsComponentLookup.erase(iter);
    } else {
        assert(false); // cannot find physics object
    }
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

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_z:
                //camera->setZoomMode(!camera->isZoomMode());
                break;
            case SDLK_d:
                // press 'd' for physics debug
                doDebugDraw = !doDebugDraw;
                if (doDebugDraw){
                    world->SetDebugDraw(&debugDraw);
                } else {
                    world->SetDebugDraw(nullptr);
                }
                break;
        }
    }
}

std::shared_ptr<GameObject> JunkDragonGame::createGameObject() {
    auto obj = std::shared_ptr<GameObject>(new GameObject());
    sceneObjects.push_back(obj);
    return obj;
}

void JunkDragonGame::createFireBall( ) {
    auto fireballObj = createGameObject();
    fireballObj->name = "Fireball";
    fireballObj->setPosition( dragonObj->getPosition() );
    fireballObj->setRotation( dragonObj->getRotation() );
    
    auto fireballController = fireballObj->addComponent<FireBallController>();

    auto fireballSprite = spriteAtlas->get("tile009.png");
    fireballSprite.setScale({1,1});
    auto fireballSpriteComponent = fireballObj->addComponent<SpriteComponent>();
    fireballSpriteComponent->setSprite(fireballSprite);

    auto fireballPhysics = fireballObj->addComponent<PhysicsComponent>();
    fireballPhysics->initCircle(b2_dynamicBody, 10/physicsScale, fireballObj->getPosition()/physicsScale, fireballObj->getRotation(), 1);
    
    auto trajectory = glm::rotateZ(glm::vec3(0,fireballController->getSpeed(),0), glm::radians(fireballObj->getRotation() ));
    fireballPhysics->setLinearVelocity( trajectory );
}
