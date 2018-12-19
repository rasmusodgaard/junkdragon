//
//  DragonController.cpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once
#include "Component.hpp"
#include "Command.hpp"

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
        
        // Constructor and preparation functions
        explicit DragonController(GameObject *gameObject);
        void setPhysicsComponent(std::shared_ptr<PhysicsComponent> pC);
        void SetAnimationControllerComponent(std::shared_ptr<AnimationControllerComponent> aC);
        
        // Dealing with key and physics 'events' 
        bool onKey(SDL_Event &event) override;
        void onCollisionStart(PhysicsComponent *comp) override;
        void onCollisionEnd(PhysicsComponent *comp) override;
        void setFireballCmd( Command fireball_cmd );

        void update(float deltaTime) override;
    
        // Power up effects
        float getFuel();
        void addFuel( float fuel_to_add);
        void addSpeedBoost(); // spoodbeest in some languages
    
        // Power down effect
        void removeFuel( float fuel_to_remove);

        // Reduce the dragon's speed
        void stop();


    private:
        std::shared_ptr<PhysicsComponent> physicsComponent;
        std::shared_ptr<AnimationControllerComponent> animationControllerComponent;

        void breathe_fire();

        Command fireball_cmd;

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
