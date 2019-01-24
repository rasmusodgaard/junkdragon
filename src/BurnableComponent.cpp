//
//  BurnableComponent.cpp
//  SRE
//

#include "BurnableComponent.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "AnimationControllerComponent.hpp"
#include "JunkDragonGame.hpp"

// Constructor. Initialize burnable parameters.
BurnableComponent::BurnableComponent(GameObject *gameObject) : Component(gameObject)
{
    onFire = false;
    life_time = F_TIME_TO_BURN;
    singed_time = F_TIME_TO_SINGE;
    destroyed = false;
}

// Setter for animation controller component
void BurnableComponent::SetAnimationControllerComponent(std::shared_ptr<AnimationControllerComponent> aC){
    animationControllerComponent = aC;
}

void BurnableComponent::update(float deltaTime){
    
    // time elapsed since being set on fire
    if (onFire) {
        life_time -= deltaTime;
        if (life_time <= singed_time) {
            animationControllerComponent->setState("singed_onfire");
        } else {
            animationControllerComponent->setState("onfire");
        }
    } else {
        // For future use: when the fire is extinguished
        if (life_time <= singed_time) {
            animationControllerComponent->setState("singed");
        }
    }

    // If our time is up, execute the burn_cmd
    if (life_time <= 0.0f && !destroyed) {
        destroyed = true;
        burnedDown();
    }
}

// Check if we were hit by a fireball
void BurnableComponent::onCollisionStart(PhysicsComponent *comp){
    if (comp->getGameObject()->name.compare("Fireball") == 0){
        onFire = true;
    }
}

// Implements command pattern
void BurnableComponent::setBurnCmd( Command burn_cmd ) {
    this->burn_cmd = burn_cmd;
}

// For future use: call when extinguished
void BurnableComponent::extinguishFire(){
    onFire = false;
}

void BurnableComponent::burnedDown(){
    burn_cmd.execute();
    // Make the game object a candidate for deletion
    deleteGameObject();
}






