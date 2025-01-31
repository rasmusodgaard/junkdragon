//
//  DragonController.cpp
//  SRE
//

#include <SDL_events.h>
#include <iostream>
#include "DragonController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include <math.h>
#include "AudioManager.hpp"
#include "SingleVarGuiComponent.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


DragonController::DragonController(GameObject *gameObject) : Component(gameObject) {
    
    // initiate dragon physics
    CW_rotation = B_CW_ROTATION;
    speed = F_DRAGON_SPEED;
    rotation_speed = F_ROTATION_SPEED;
    
    // fire breathing parameters
    breathing_fire          = B_BREATHING_FIRE;
    last_fire_ball          = F_LAST_FIRE_BALL;
    cool_down               = F_COOL_DOWN;
    fuel                    = F_FUEL;
    fuel_recovery           = F_FUEL_RECOVERY;
    fireBallFuelCost        = F_FIREBALLFUELCOST;
    speed_boost             = 0.0f;
    speed_boost_decrement   = F_SPEED_BOOST_DECREMENT;
}


void DragonController::setPhysicsComponent(std::shared_ptr<PhysicsComponent> pC){
    physicsComponent = pC;
}

void DragonController::SetAnimationControllerComponent(std::shared_ptr<AnimationControllerComponent> aC){
    animationControllerComponent = aC;
}

bool DragonController::onKey(SDL_Event &event) {
    if (event.key.keysym.sym == SDLK_LEFT) {
        if (event.type == SDL_KEYDOWN) {
            CW_rotation = false;
        }
    }

    if (event.key.keysym.sym == SDLK_RIGHT) {
        if (event.type == SDL_KEYDOWN) {
            CW_rotation = true;
        }
    }

    if (event.key.keysym.sym == SDLK_SPACE) {
        if (event.type == SDL_KEYDOWN) {
            this->breathing_fire = true;
            if (fuel < fireBallFuelCost) {
                AudioManager::instance->PlaySound(AudioManager::cough);
            }
        }
        if (event.type == SDL_KEYUP) {
            this->breathing_fire = false;
        }
    }

    return false;
}

void DragonController::onCollisionStart(PhysicsComponent *comp) {

}

void DragonController::onCollisionEnd(PhysicsComponent *comp) {
    
}

void DragonController::breathe_fire() {
    fireball_cmd.execute();
    fuel = fuel - fireBallFuelCost;
    AudioManager::instance->PlaySound(AudioManager::breathe_fire);
}

void DragonController::setFireballCmd( Command fireball_cmd ) {
    this->fireball_cmd = fireball_cmd;
}

void DragonController::update(float deltaTime) {
    glm::vec2 position = this->getGameObject()->getPosition();
    float rotation = this->getGameObject()->getRotation();
    float magnitude = deltaTime * (speed + speed_boost);
    glm::vec2 velocity = glm::rotateZ(glm::vec3(0,magnitude,0), glm::radians(rotation));
    physicsComponent->setLinearVelocity(velocity);
    
    // Update rotation of dragon
    if(CW_rotation) {
        physicsComponent->setAngularVelocity(-angularVelocity);
         this->getGameObject()->setRotation(rotation - rotation_speed);
    } else {
        physicsComponent->setAngularVelocity(angularVelocity);
        this->getGameObject()->setRotation(rotation + rotation_speed);
    }
    
    // Move the head
    this->getGameObject()->setPosition( position + velocity );
    if(breathing_fire){
        if(last_fire_ball >= cool_down && fuel >= fireBallFuelCost ) {
            last_fire_ball = 0.0f;
            breathe_fire();
        }
    }

    // Increase time since last fireball
    last_fire_ball += deltaTime;

    speed_boost = fmax(speed_boost - speed_boost_decrement, 0.0f);

    fuel += fuel_recovery;

    this->getGameObject()->getComponent<SingleVarGuiComponent>()->setVal(fuel);
}

float DragonController::getFuel() {
    return this->fuel;
}

// Pickup functions
void DragonController::addFuel( float fuel_to_add) {
    this->fuel += fuel_to_add;
}

void DragonController::removeFuel( float fuel_to_remove) {
    this->fuel -= fuel_to_remove;
}

void DragonController::addSpeedBoost() {
    this->speed_boost += F_SPEED_BOOST;
}

void DragonController::stop() {
    this->speed = 0.0f;
}
