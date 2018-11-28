#pragma once

#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include <vector>
#include "Box2D/Dynamics/b2World.h"
#include "GameObject.hpp"
#include "DragonController.hpp"
#include "FloatTrackComponent.hpp"
#include "CameraFollow.hpp"
#include "BackgroundComponent.hpp"
#include "Box2DDebugDraw.hpp"
#include "Level.hpp"



class PhysicsComponent;

class JunkDragonGame : public b2ContactListener {
public:
    JunkDragonGame();
    static JunkDragonGame* instance;
    static const glm::vec2 windowSize;
    
    // Gameobject existance
    std::shared_ptr<GameObject> createGameObject();
    void createFireBall( );
    void createHouse( glm::vec2 pos );

    // Physics
    static constexpr float32 timeStep = 1.0f / 60.0f;
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

private:
    std::shared_ptr<Level> level;
    std::shared_ptr<CameraFollow> camera;
    std::shared_ptr<sre::SpriteAtlas> spriteAtlas;
    std::vector<std::shared_ptr<GameObject>> sceneObjects;

    BackgroundComponent backgroundComponent;    

    sre::SDLRenderer r;
    
    void init();
    void initPhysics();
    void buildGUI();
    void update(float time);
    void updatePhysics();
    void render();
    void onKey(SDL_Event &event);
    void handleContact(b2Contact *contact, bool begin);
    
    std::shared_ptr<GameObject> dragonObj;
    std::shared_ptr<FloatTrackComponent> fuelTrackComp;
    std::shared_ptr<FloatTrackComponent> scoreTrackComp;

    // Physics members
    b2World * world = nullptr;
    const float physicsScale = 100;
    void registerPhysicsComponent(PhysicsComponent *r);
    void deregisterPhysicsComponent(PhysicsComponent *d);
    std::map<b2Fixture*,PhysicsComponent *> physicsComponentLookup;
    Box2DDebugDraw debugDraw;
    bool doDebugDraw = false;
    friend class PhysicsComponent;

    // Game globals
    float score;
};
