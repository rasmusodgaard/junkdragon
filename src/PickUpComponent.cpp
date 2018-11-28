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
    
}

void PickUpComponent::update(float deltaTime){
    
}

void PickUpComponent::onCollisionStart(PhysicsComponent *comp){
    if (comp->getGameObject()->name.compare("Dragon") == 0){
        cmd.execute();

    }
}

void PickUpComponent::SetCommand(Command _cmd){
    cmd = _cmd;
}









