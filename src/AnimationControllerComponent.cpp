//
//  AnimationControllerComponent.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "AnimationControllerComponent.hpp"
#include "GameObject.hpp"
#include <memory>
#include <iostream>

AnimationControllerComponent::AnimationControllerComponent(GameObject *gameObject) : Component(gameObject) {
// Constructor
}

void AnimationControllerComponent::update(float deltaTime) {
    auto spriteComponent = gameObject->getComponent<SpriteComponent>();
    assert(spriteComponent != nullptr);

    time += deltaTime;
    
    float animationTime = currState->animationTime;
    
    // If the animation time has elapsed, update the sprite
    if (time > animationTime){
        time = fmod(time, animationTime);
        spriteIndex = (spriteIndex + 1) % currState->sprites.size();
        spriteComponent->setSprite( currState->sprites[spriteIndex] );
    }
}

void AnimationControllerComponent::addState(std::string label, float animationTime, std::vector<sre::Sprite> sprites) {
    AnimationState aS;
    
    // Grab the variables
    aS.label            = label;
    aS.animationTime    = animationTime;
    aS.sprites          = sprites;

    // For development: check if a state already exists with this label
    auto testState = findState(label);
    assert(testState == nullptr);

    for (auto & sprite : aS.sprites) {
        sprite.setOrderInBatch(this->orderInBatch);
    }
    
    aStates.push_back( aS ); 
    currState = &aStates[0];
}

// Set the animation to a given state
// Return 0 if the lavel is not found
int AnimationControllerComponent::setState(std::string label) {
    currState = findState(label);
    assert(currState != nullptr);
    return 0; // all good
}

// Loop through and set the scale of each of the sprites in the vector
void AnimationControllerComponent::setScale(glm::vec2 i_scale) {
        sprite_scale = i_scale;
        
        for (auto & aState : aStates){
            for (auto & sprite : aState.sprites)
            sprite.setScale(this->sprite_scale);
        }
}

// Find the state matching a given label
//  Return nullptr if not found
AnimationState* AnimationControllerComponent::findState(std::string label) {
    for (auto & aState: aStates) {
        if (aState.label == label) {
            return &aState;
        }
    }

    return nullptr;
}

// Set layer of the sprites. High number is 'closer' to camera
void AnimationControllerComponent::setLayer( uint16_t orderInBatch ) {
    this->orderInBatch = orderInBatch;
}