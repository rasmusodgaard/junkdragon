//
//  BurnableComponent.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//

#include "BurnableComponent.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
//#include "JunkDragonGame.hpp"




BurnableComponent::BurnableComponent(GameObject *gameObject) : Component(gameObject)
{
    onFire = false;
    life_time = 3;
}

void BurnableComponent::update(float deltaTime){
    
    // time elapsed since being set on fire
    if (onFire) {
        time_elapsed += deltaTime;
    }
    
    // object burned down
    if (time_elapsed >= life_time) {
        burnedDown();
    
    }
}

void BurnableComponent::onCollisionStart(PhysicsComponent *comp){
    if (comp->getGameObject()->name.compare("Fireball") == 0){
        onFire = true;
    }
}

void BurnableComponent::extinguishFire(){
    onFire = false;
}

void BurnableComponent::burnedDown(){
    
}






