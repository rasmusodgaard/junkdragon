#pragma once

#include "Component.hpp"

class PhysicsComponent;
class AnimationControllerComponent;

class DragonController : public Component {
    public:
        explicit DragonController(GameObject *gameObject);
        void setPhysicsComponent(std::shared_ptr<PhysicsComponent> pC);
        void SetAnimationControllerComponent(std::shared_ptr<AnimationControllerComponent> aC);
        bool onKey(SDL_Event &event) override;

        void onCollisionStart(PhysicsComponent *comp) override;
    
        void onCollisionEnd(PhysicsComponent *comp) override;

        void update(float deltaTime) override;
    
        float getFuel();

    private:
        std::shared_ptr<PhysicsComponent> physicsComponent;
        std::shared_ptr<AnimationControllerComponent> animationControllerComponent;

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
