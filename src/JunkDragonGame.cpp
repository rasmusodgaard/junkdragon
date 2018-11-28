#include "JunkDragonGame.hpp"
#include <iostream>
#include "GameObject.hpp"
#include "sre/RenderPass.hpp"
#include "SpriteComponent.hpp"
#include "AnimationControllerComponent.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "PhysicsComponent.hpp"
#include "FloatTrackComponent.hpp"
#include <sre/Inspector.hpp>
#include "DragonController.hpp"
#include "FireBallController.hpp"
#include "BurnableComponent.hpp"
#include "PickUpComponent.hpp"
#include "Command.hpp"

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
    
    ImGuiIO& io = ImGui::GetIO();

    init();
    buildGUI();

    
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

void JunkDragonGame::buildGUI() {
    auto fuelTrackerObj = createGameObject();
    fuelTrackComp = fuelTrackerObj->addComponent<FloatTrackComponent>();
    fuelTrackComp->setLabel("Fuel");
    fuelTrackComp->setVal( dragonObj->getComponent<DragonController>()->getFuel() );
    fuelTrackComp->setPos(0.0f, 0.1f); // y val not currently used. It is a function of size
    fuelTrackComp->setSize(0.3f, 0.1f);

    auto scoreTrackerObj = createGameObject();
    scoreTrackComp = fuelTrackerObj->addComponent<FloatTrackComponent>();
    scoreTrackComp->setLabel("Score");
    scoreTrackComp->setVal( dragonObj->getComponent<DragonController>()->getFuel() );
    scoreTrackComp->setPos(0.7f, 0.1f); // y val not currently used. It is a function of size
    scoreTrackComp->setSize(0.3f, 0.1f);
}

void JunkDragonGame::init(){
    initPhysics();
    
    // init game junk
    score = 0.0f;

    spriteAtlas = sre::SpriteAtlas::create("junkdragon.json","junkdragon.png");

    level = std::make_shared<Level>();
    level->GenerateLevel();
    
    auto camObj = createGameObject();
    camera = camObj->addComponent<CameraFollow>();
    
    // Dragon Game Object (Player)
    dragonObj = createGameObject();
    dragonObj->name = "Dragon";
    camera->setFollowObject(dragonObj, {0,0});
    glm::vec2 spawnPosition = level->GetStartingPosition();
    dragonObj->setPosition(spawnPosition);
    dragonObj->setRotation(0.0f);
    // Add controller
    auto dragonC = dragonObj->addComponent<DragonController>();
    //dragonC->setFireballCreator( createFireBall() );
    // Add sprite component
    auto sprite = spriteAtlas->get("dragon_11.png");
    sprite.setScale({3,3}); 
    auto spriteC = dragonObj->addComponent<SpriteComponent>();
    spriteC->setSprite(sprite);
    // Add animatinos
    auto animCC = dragonObj->addComponent<AnimationControllerComponent>();
    
    animCC->addState(
        "flying",
        0.2f,
        {spriteAtlas->get("dragon_11.png"), spriteAtlas->get("dragon_12.png"), spriteAtlas->get("dragon_11.png"), spriteAtlas->get("dragon_10.png")}
        );

    animCC->setScale({3,3});
    animCC->setState("flying");

    dragonC->SetAnimationControllerComponent( animCC );
    
    auto DragonPhysics = dragonObj->addComponent<PhysicsComponent>();
    dragonC->setPhysicsComponent(dragonObj->getComponent<PhysicsComponent>());

    DragonPhysics->initCircle(b2_dynamicBody, 30/physicsScale, dragonObj->getPosition()/physicsScale, dragonObj->getRotation(), 1);
    DragonPhysics->setSensor(true);

    // Add background
    backgroundComponent.init("background.png", {-2000,-2000}, {10000, 10000}, 50);
    

    // Add Houses
    createHouse({   0, 800});
    createHouse({ 250, 900});
    createHouse({ 500,1000});
    createHouse({ 750, 900});
    createHouse({1000, 800});
    
    // Add pickups
    createPickUp({200, 200}, spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addFuel ) );
    createPickUp({600, 200}, spriteAtlas->get("chilli.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    createPickUp({800, 200}, spriteAtlas->get("chilli.png"), Command( dragonC->self, &DragonController::addSpeedBoost ) );
    createPickUp({1000, 200}, spriteAtlas->get("donut.png"), Command( dragonC->self, &DragonController::addFuel ) );


    
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

    fuelTrackComp->setVal( dragonObj->getComponent<DragonController>()->getFuel() );
    scoreTrackComp->setVal( this->score);
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

    // Render the GUI components last
    for (auto & go : sceneObjects){
        for (auto & comp : go->getComponents()){
            comp->onGui();
        }
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
                // camera->setZoomMode(!camera->isZoomMode());
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

    auto fireballSprite = spriteAtlas->get("fireball_3.png");
    
    fireballSprite.setScale({0.5,0.5});
    auto fireballSpriteComponent = fireballObj->addComponent<SpriteComponent>();
    fireballSpriteComponent->setSprite(fireballSprite);

    auto fireballACC = fireballObj->addComponent<AnimationControllerComponent>();

    // Could animate the not burning buildings
    fireballACC->addState(
        "shooting",
        0.1f,
        {spriteAtlas->get("fireball_1.png"),spriteAtlas->get("fireball_2.png"),spriteAtlas->get("fireball_3.png"),spriteAtlas->get("fireball_4.png")}
        );
    
    fireballACC->setScale({0.8,0.8});
    fireballACC->setState("shooting");

    auto fireballPhysics = fireballObj->addComponent<PhysicsComponent>();
    fireballPhysics->initCircle(b2_dynamicBody, 10/physicsScale, fireballObj->getPosition()/physicsScale, fireballObj->getRotation(), 1);
    
    auto trajectory = glm::rotateZ(glm::vec3(0,fireballController->getSpeed(),0), glm::radians(fireballObj->getRotation() ));
    fireballPhysics->setLinearVelocity( trajectory );
}

void JunkDragonGame::createHouse( glm::vec2 pos ) {
    auto HouseObj = createGameObject();
    HouseObj->setPosition(pos);
    HouseObj->setRotation(0.0f);
    auto houseSprite = spriteAtlas->get("farmhouse_2.png");
    auto houseSpriteC = HouseObj->addComponent<SpriteComponent>();
    houseSprite.setScale({1,1});
    houseSpriteC->setSprite(houseSprite);
    auto houseBC = HouseObj->addComponent<BurnableComponent>();
    
    auto HousePhysics = HouseObj->addComponent<PhysicsComponent>();
    HousePhysics->initCircle(b2_staticBody, 50/physicsScale, HouseObj->getPosition()/physicsScale, HouseObj->getRotation(), 1);
    HousePhysics->setSensor(true);

    auto houseACC = HouseObj->addComponent<AnimationControllerComponent>();

    // Could animate the not burning buildings
    houseACC->addState(
        "notburning",
        1.0f,
        {spriteAtlas->get("farmhouse_2.png")}
        );
    houseACC->addState(
        "onfire",
        0.1f,
        {spriteAtlas->get("farmhouse_2_burn1.png"), spriteAtlas->get("farmhouse_2_burn2.png")}
        );
    houseACC->addState(
        "singed",
        1.0f,
        {spriteAtlas->get("farmhouse_3.png")}
        );
    houseACC->addState(
        "singed_onfire",
        0.1f,
        {spriteAtlas->get("farmhouse_3_burn1.png"), spriteAtlas->get("farmhouse_3_burn2.png")}
        );
    
    houseACC->setScale({1,1});
    houseACC->setState("notburning");

    houseBC->SetAnimationControllerComponent( houseACC );
}

void JunkDragonGame::createPickUp(glm::vec2 pos, sre::Sprite pickUpSprite, Command cmd) {
    auto PUObj = createGameObject();
    PUObj->setPosition(pos);
    PUObj->setRotation(0.0f);
    
    pickUpSprite.setScale({0.5,0.5});
    auto PUSpriteC = PUObj->addComponent<SpriteComponent>();
    PUSpriteC->setSprite(pickUpSprite);
    auto pickUpC = PUObj->addComponent<PickUpComponent>();
    pickUpC -> SetCommand( cmd );
    
    auto PUPhys = PUObj->addComponent<PhysicsComponent>();
    PUPhys->initCircle(b2_staticBody, 30/physicsScale, PUObj->getPosition()/physicsScale, PUObj->getRotation(), 1);
    PUPhys->setSensor(true);
}