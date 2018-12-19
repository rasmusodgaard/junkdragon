#include "JunkDragonGame.hpp"
#include <iostream>
#include "sre/RenderPass.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "PhysicsComponent.hpp"
#include "FloatTrackComponent.hpp"
#include <sre/Inspector.hpp>
#include <math.h>
#include "Command.hpp"
#include "AudioManager.hpp"
#include "StartState.hpp"
#include "PlayingState.hpp"
#include "EndState.hpp"

const glm::vec2 JunkDragonGame::windowSize(INT_WINDOWSIZE_HEIGHT, INT_WINDOWSIZE_WIDTH);
JunkDragonGame* JunkDragonGame::instance = nullptr;

JunkDragonGame::JunkDragonGame():debugDraw(physicsScale) {
    
    instance = this;
    
    r.setWindowSize(windowSize);
    r.init()
    .withSdlInitFlags(SDL_INIT_EVERYTHING)
    .withSdlWindowFlags(SDL_WINDOW_OPENGL);
    
    new AudioManager();

    
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


    // Create the various game states
    gs_startstate   = std::shared_ptr<GameState>( new StartState() );
    gs_playingstate = std::shared_ptr<GameState>( new PlayingState() );
    if(auto ps = std::dynamic_pointer_cast<PlayingState>(gs_playingstate) ) {
        ps->setNextLevelToLoad("level2.json");
    }
    gs_endstate     = std::shared_ptr<GameState>( new EndState() );
    changeState(gs_startstate);

}

void JunkDragonGame::update(float time){
    gs_currentstate->update(time);
}

void JunkDragonGame::render() {

    auto rp = sre::RenderPass::create()
            .withCamera(gs_currentstate->camera->getCamera())
            .build();
    
    gs_currentstate->backgroundComponent.renderBackground(rp,0.0f);

    auto spriteBatchBuilder = sre::SpriteBatch::create();
    
    for (auto & go : gs_currentstate->sceneObjects){
        go->renderSprite(spriteBatchBuilder);
    }
    
    gs_currentstate->render(rp);

    auto sb = spriteBatchBuilder.build();
    rp.draw(sb);

    if (doDebugDraw){
        static sre::Inspector profiler;
        profiler.update();
        profiler.gui(false);

        world->DrawDebugData();
        rp.drawLines(debugDraw.getLines());
        debugDraw.clear();
    }

    // Render the GUI components last
    for (auto & go : gs_currentstate->sceneObjects){
        for (auto & comp : go->getComponents()){
            comp->onGui();
        }
    }

    
}

void JunkDragonGame::updatePhysics() {
    const int positionIterations = INT_POSITION_ITERATIONS;
    const int velocityIterations = INT_VELOCITY_ITERATIONS;
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
    float gravity = F_GRAVITY;
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

void JunkDragonGame::endTheGame() {
    changeState(gs_endstate);
}

void JunkDragonGame::startTheGame() {
    changeState(gs_playingstate);
}

void JunkDragonGame::recordScore( float final_score ) {
    if(auto es = std::dynamic_pointer_cast<EndState>(gs_endstate) ) {
        es->recordScore( final_score );
    }
}

void JunkDragonGame::incrementLevel( ) {
    if(auto ps = std::dynamic_pointer_cast<PlayingState>(gs_playingstate) ) {
        ps->setNextLevelToLoad(levels[ (current_level+1) % N_LEVELS ]);
    }
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

    gs_currentstate->onKey(event);
    
    for (auto & gameObject: gs_currentstate->sceneObjects) {
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



void JunkDragonGame::changeState( std::shared_ptr<GameState> gs_state ) {
    gs_nextstate = gs_state;

    if(gs_currentstate != nullptr) {
        gs_currentstate->exitState();
    }
    gs_nextstate->enterState();

    gs_currentstate = gs_nextstate;
    gs_nextstate = nullptr;

}
