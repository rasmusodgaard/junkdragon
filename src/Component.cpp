//
//  Component.hpp
//  SRE
//
//  Created by John O'Donnell
//

#include "Component.hpp"
#include "GameObject.hpp"
#include <iostream>

Component::Component(GameObject *gameObject)
:gameObject(gameObject)
{
}

void Component::renderSprite(sre::SpriteBatch::SpriteBatchBuilder &spriteBatchBuilder) {

}

void Component::update(float deltaTime) {

}

GameObject *Component::getGameObject() {
    return gameObject;
}

void Component::printy(){
    std::cout << "PRINTY" << std::endl;
}

bool Component::onKey(SDL_Event &event) {
    return false;
}

void Component::onCollisionStart(PhysicsComponent* comp) {

}

void Component::onCollisionEnd(PhysicsComponent* comp) {

}

//communicates from the component, sets a flag in the gameObject that makes it a candidate for being deleted
void Component::deleteGameObject(){
    this->getGameObject()->setDeleteMe(true);
}

void Component::onGui(){

}
