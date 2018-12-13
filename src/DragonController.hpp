//
//  DragonController.cpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once
#include "Component.hpp"

#define B_CW_ROTATION       true
#define B_BREATHING_FIRE    false

#define F_DRAGON_SPEED            400.0f
#define F_ROTATION_SPEED            2.0f
#define F_LAST_FIRE_BALL        	0.0f
#define F_COOL_DOWN                 0.1f
#define F_FUEL                     10.0f
#define F_FUEL_RECOVERY             0.001f
#define F_FIREBALLFUELCOST          0.5f
#define F_SPEED_BOOST             200.0f
#define F_SPEED_BOOST_DECREMENT     0.5f

class PhysicsComponent;
class AnimationControllerComponent;

class DragonController : public Component {
    public:
        DragonController *self;
        
        explicit DragonController(GameObject *gameObject);
        void setPhysicsComponent(std::shared_ptr<PhysicsComponent> pC);
        void SetAnimationControllerComponent(std::shared_ptr<AnimationControllerComponent> aC);
        bool onKey(SDL_Event &event) override;

        void onCollisionStart(PhysicsComponent *comp) override;
    
        void onCollisionEnd(PhysicsComponent *comp) override;

        void update(float deltaTime) override;
    
        float getFuel();

        // Power up effects
        void addFuel();
        void addSpeedBoost(); // spoodbeest in some languages

        void stop();

    private:
        std::shared_ptr<PhysicsComponent> physicsComponent;
        std::shared_ptr<AnimationControllerComponent> animationControllerComponent;

        void breathe_fire();

        bool CW_rotation;
        bool breathing_fire;
        float last_fire_ball;
        float cool_down;
        
        float fuel;
        float fuel_recovery;
        float fireBallFuelCost;

        float speed;
        float speed_boost;
        float speed_boost_decrement;
        float rotation_speed;
        float angularVelocity = 90;
    
};
