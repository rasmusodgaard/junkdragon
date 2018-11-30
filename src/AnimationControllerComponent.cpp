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

}

void AnimationControllerComponent::update(float deltaTime) {
    auto spriteComponent = gameObject->getComponent<SpriteComponent>();
    assert(spriteComponent != nullptr);

    time += deltaTime;
    
    float animationTime = currState->animationTime;
    
    if (time > animationTime){
        time = fmod(time, animationTime);
        spriteIndex = (spriteIndex + 1) % currState->sprites.size();
        spriteComponent->setSprite( currState->sprites[spriteIndex] );
    }
}

void AnimationControllerComponent::addState(std::string label, float animationTime, std::vector<sre::Sprite> sprites) {
    AnimationState aS;
    
    aS.label            = label;
    aS.animationTime    = animationTime;
    aS.sprites          = sprites;

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

// float AnimationControllerComponent::getAnimationTimeForState(std::string label) const {
    
//     // TODO
//     return 0.0f;
// }   

// void AnimationControllerComponent::setAnimationTimeForState( AnimationState * newAnimationState, float time ) {
//     // TODO
// }

void AnimationControllerComponent::setScale(glm::vec2 i_scale) {
        sprite_scale = i_scale;
        
        for (auto & aState : aStates){
            for (auto & sprite : aState.sprites)
            sprite.setScale(this->sprite_scale);
        }
}

// Find the state matching a given label
//  Return 0 if not found
AnimationState* AnimationControllerComponent::findState(std::string label) {
    for (auto & aState: aStates) {
        if (aState.label == label) {
            return &aState;
        }
    }

    return nullptr;
}

void AnimationControllerComponent::setLayer( uint16_t orderInBatch ) {
    this->orderInBatch = orderInBatch;
}