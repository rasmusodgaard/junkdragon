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

#define F_GRAVITY                       0.0f

#define INT_POSITION_ITERATIONS         4
#define INT_VELOCITY_ITERATIONS        12
#define INT_WINDOWSIZE_HEIGHT         800
#define INT_WINDOWSIZE_WIDTH          600
#define INT_DRAGON_SCALE                3
#define INT_BACKGROUND_RESOLUTION      50
#define INT_BACKGROUND_STARTPOS     -2000
#define INT_BACKGROUND_SIZE          4000
#define INT_WALL_THICKNESS             50
#define F_ROTATION_NORTH                0.0f
#define F_WALL_THICKNESS               50.0f
#define F_FIREBALL_OFFSET             120.0f

// Layers
#define U_GROUND_LAYER                 1
#define U_POWERUP_LAYER                2
#define U_FIREBALL_LAYER               3
#define U_DRAGON_LAYER                 4

class Command;
class PhysicsComponent;
class GameState;

class JunkDragonGame : public b2ContactListener {
public:
    JunkDragonGame();
    static JunkDragonGame* instance;
    static const glm::vec2 windowSize;
    
    // Gameobject existance
    std::shared_ptr<GameObject> createGameObject();
    void createFireBall( );
    void createHouse( glm::vec2 pos );
    void createPickUp( glm::vec2 pos, sre::Sprite pickUpSprite, Command cmd );
    void createWalls(glm::vec2 dimensions, int thickness);

    // Physics
    static constexpr float32 timeStep = 1.0f / 60.0f;
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

    // Scoring mechanisms
    void increaseScore(float i_score);
    void decrementHouses();

    void changeState(std::shared_ptr<GameState> gs_state);

private:
    std::shared_ptr<Level> currentLevel;
    std::shared_ptr<CameraFollow> camera;
    std::shared_ptr<sre::SpriteAtlas> spriteAtlas;
    std::vector<std::shared_ptr<GameObject>> sceneObjects;

    BackgroundComponent backgroundComponent;
    
    // Walls
    std::shared_ptr<GameObject> wallTop;
    std::shared_ptr<GameObject> wallBottom;
    std::shared_ptr<GameObject> wallLeft;
    std::shared_ptr<GameObject> wallRight;
    
    std::shared_ptr<GameState> gs_currentstate = nullptr;
    std::shared_ptr<GameState> gs_nextstate;
    std::shared_ptr<GameState> gs_playingstate;
    std::shared_ptr<GameState> gs_endstate;

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
    std::shared_ptr<FloatTrackComponent> houseTrackComp;
    std::shared_ptr<FloatTrackComponent> timeTrackComp;


    bool checkGameOver();

    // Physics members
    b2World * world = nullptr;
    const float physicsScale = 100;
    void registerPhysicsComponent(PhysicsComponent *r);
    void deregisterPhysicsComponent(PhysicsComponent *d);
    std::map<b2Fixture*,PhysicsComponent *> physicsComponentLookup;
    Box2DDebugDraw debugDraw;
    bool doDebugDraw = false;
    friend class PhysicsComponent;
    friend class PlayingState;
    friend class EndState;

    bool    burnination_has_begun;
    float   time_elapsed;
    float   time_remaining;
    int     n_houses;

    // Game globals
    float score;
    bool game_over;
};
