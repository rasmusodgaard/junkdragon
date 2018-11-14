#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include <vector>
#include "Box2D/Dynamics/b2World.h"
#include "GameObject.hpp"
#include "DragonController.hpp"
#include "CameraFollow.hpp"
#include "BackgroundComponent.hpp"
//#include "Box2DDebugDraw.hpp"

class JunkDragonGame {
public:
    JunkDragonGame();
    static JunkDragonGame* instance;
    static const glm::vec2 windowSize;
    std::shared_ptr<GameObject> createGameObject();
    void createFireBall( );
 
private:
    
    std::shared_ptr<CameraFollow> camera;
    std::shared_ptr<sre::SpriteAtlas> spriteAtlas;
    std::vector<std::shared_ptr<GameObject>> sceneObjects;

    BackgroundComponent backgroundComponent;    

    sre::SDLRenderer r;
    
    void init();
    
    void update(float time);
    
    void render();
    
    void onKey(SDL_Event &event);
    
    std::shared_ptr<GameObject> dragonObj;
};
