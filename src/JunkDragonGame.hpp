#pragma once

#include "sre/SDLRenderer.hpp"
#include <vector>
#include "Box2D/Dynamics/b2World.h"
#include "GameObject.hpp"
#include "DragonController.hpp"
#include "SingleVarGuiComponent.hpp"
#include "CameraFollow.hpp"
#include "BackgroundComponent.hpp"
#include "Box2DDebugDraw.hpp"

#define F_PHYSICS_TIMESTEP              0.3f
#define F_GRAVITY                       0.0f
#define INT_POSITION_ITERATIONS         4
#define INT_VELOCITY_ITERATIONS        12
#define INT_WINDOWSIZE_HEIGHT         600
#define INT_WINDOWSIZE_WIDTH          800
//#define N_LEVELS                        3

class Command;
class PhysicsComponent;
class GameState;

class JunkDragonGame : public b2ContactListener {
public:
    JunkDragonGame();
    static JunkDragonGame* instance;
    static const glm::vec2 windowSize;
    
    // Physics
    static constexpr float32 timeStep = 1.0f / 60.0f;
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

    // Scoring mechanisms
    void increaseScore(float i_score);
    void decrementHouses();

    void changeState(std::shared_ptr<GameState> gs_state);
    void endTheGame( bool goodend, int score);
    void startTheGame();
    void transition();
    void incrementLevel();

private:
    
    const float physicsScale = 100;

    std::shared_ptr<GameState> gs_currentstate = nullptr;
    std::shared_ptr<GameState> gs_nextstate;
    std::shared_ptr<GameState> gs_startstate;
    std::shared_ptr<GameState> gs_playingstate;
    std::shared_ptr<GameState> gs_transition;
    std::shared_ptr<GameState> gs_endstate;

    sre::SDLRenderer r;

    int current_level = 0;
    std::vector<std::string> levels = {"level1.json", "level2.json", "level3.json"};
    
    void init();
    void initPhysics();
    void update(float time);
    void updatePhysics();
    void render();
    void onKey(SDL_Event &event);
    void handleContact(b2Contact *contact, bool begin);
    
    // Physics members
    b2World * world = nullptr;
    void registerPhysicsComponent(PhysicsComponent *r);
    void deregisterPhysicsComponent(PhysicsComponent *d);
    std::map<b2Fixture*,PhysicsComponent *> physicsComponentLookup;
    Box2DDebugDraw debugDraw;
    bool doDebugDraw = false;
    friend class PhysicsComponent;
};
