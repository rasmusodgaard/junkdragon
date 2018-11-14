#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include <vector>
#include "Box2D/Dynamics/b2World.h"
#include "GameObject.hpp"
#include "DragonController.hpp"
#include "CameraFollow.hpp"
#include "BackgroundComponent.hpp"
//#include "Box2DDebugDraw.hpp"

class PhysicsComponent;

class JunkDragonGame : public b2ContactListener {
public:
    JunkDragonGame();
    static JunkDragonGame* instance;
    static const glm::vec2 windowSize;
    
    // Gameobject existance
    std::shared_ptr<GameObject> createGameObject();
    void createFireBall( );

    // Physics
    static constexpr float32 timeStep = 1.0f / 60.0f;
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;

private:
    
    std::shared_ptr<CameraFollow> camera;
    std::shared_ptr<sre::SpriteAtlas> spriteAtlas;
    std::vector<std::shared_ptr<GameObject>> sceneObjects;

    BackgroundComponent backgroundComponent;    

    sre::SDLRenderer r;
    
    void init();
    void initPhysics();
    void update(float time);
    void updatePhysics();
    void render();
    void onKey(SDL_Event &event);
    void handleContact(b2Contact *contact, bool begin);
    
    std::shared_ptr<GameObject> dragonObj;

    // Physics members
    b2World * world = nullptr;
    const float physicsScale = 100;
    void registerPhysicsComponent(PhysicsComponent *r);
    void deregisterPhysicsComponent(PhysicsComponent *d);
    std::map<b2Fixture*,PhysicsComponent *> physicsComponentLookup;
    friend class PhysicsComponent;
};
