//
//  MenuOptionComponent.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 21/11/2018.
//

#pragma once
#include "MenuOptionComponent.hpp"

MenuOptionComponent::MenuOptionComponent(GameObject *gameObject) : Component(gameObject)
{
    // TODO what does a button need?
    highlighted = false;
}

void MenuOptionComponent::update(float deltaTime){
    
}
