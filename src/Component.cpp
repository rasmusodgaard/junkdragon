//
//  Component.hpp
//  SRE
//
//  Created by John O'Donnell
//

#include "Component.hpp"
#include "GameObject.hpp"

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

bool Component::onKey(SDL_Event &event) {
    return false;
}

void Component::onCollisionStart(PhysicsComponent* comp) {

}

void Component::onCollisionEnd(PhysicsComponent* comp) {

}

void Component::deleteGameObject(){
    this->getGameObject()->setDeleteMe(true);
}

void Component::onGui(){

}