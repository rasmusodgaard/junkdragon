//
//  PickUpComponent.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 21/11/2018.
//

#include "PickUpComponent.hpp"
#include "GameObject.hpp"
#include "PhysicsComponent.hpp"

#include <iostream>

PickUpComponent::PickUpComponent(GameObject *gameObject) : Component(gameObject)
{
    pickedUp = F_PICKEDUP;
}

void PickUpComponent::update(float deltaTime){
    
}

void PickUpComponent::onCollisionStart(PhysicsComponent *comp){
    if (comp->getGameObject()->name.compare("Dragon") == 0 && !pickedUp){
        pickedUp = true;
        cmd.execute();
        deleteGameObject();
    }
}

void PickUpComponent::SetCommand(Command _cmd){
    cmd = _cmd;
}









