//
//  BurnableComponent.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//

#include "BurnableComponent.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "AnimationControllerComponent.hpp"
#include "JunkDragonGame.hpp"

BurnableComponent::BurnableComponent(GameObject *gameObject) : Component(gameObject)
{
    onFire = false;
    life_time = 6.0f;
    singed_time = life_time / 2.0f;
    destroyed = false;
}

void BurnableComponent::SetAnimationControllerComponent(std::shared_ptr<AnimationControllerComponent> aC){
    animationControllerComponent = aC;
}

void BurnableComponent::update(float deltaTime){
    
    // time elapsed since being set on fire
    if (onFire) {
        life_time -= deltaTime;
        if (life_time <= singed_time) {
            animationControllerComponent->setState("singed_onfire");
        }
    } else {
        if (life_time <= singed_time) {
            animationControllerComponent->setState("singed");
        }
    }

    if (life_time <= 0.0f && !destroyed) {
        destroyed = true;
        burnedDown();
    }
}


void BurnableComponent::onCollisionStart(PhysicsComponent *comp){
    if (comp->getGameObject()->name.compare("Fireball") == 0){
        onFire = true;
        animationControllerComponent->setState("onfire");
    }
}

void BurnableComponent::extinguishFire(){
    onFire = false;
}

void BurnableComponent::burnedDown(){
    JunkDragonGame::instance->increaseScore(100.0f);
    JunkDragonGame::instance->decrementHouses();
    deleteGameObject();
}






