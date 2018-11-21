#pragma once

#include "Component.hpp"

class DragonController : public Component {
    public:
        explicit DragonController(GameObject *gameObject);
        void setPhysicsComponent(std::shared_ptr<PhysicsComponent> pc);
        bool onKey(SDL_Event &event) override;

        void onCollisionStart(PhysicsComponent *comp) override;
    
        void onCollisionEnd(PhysicsComponent *comp) override;

        void update(float deltaTime) override;
    
        float getFuel();

    private:
        std::shared_ptr<PhysicsComponent> physicsComponent;

        void breathe_fire();

        bool CW_rotation;
        bool breathing_fire;
        float last_fire_ball;
        float cool_down;
        
        float fuel;
        float fireBallFuelCost;

        float speed;
        float rotation_speed;
        float angularVelocity = 90;
    
};
