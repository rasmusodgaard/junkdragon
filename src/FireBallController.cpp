//
//  FireBallController.cpp
//  SRE
//

#include <SDL_events.h>
#include <iostream>
#include "FireBallController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "JunkDragonGame.hpp"
#include "PhysicsComponent.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

FireBallController::FireBallController(GameObject *gameObject) : Component(gameObject) {

    speed = F_FIREBALL_SPEED;
    time_elapsed = F_TIME_ELAPSED;
    life_time = F_LIFE_TIME;
}

void FireBallController::onCollisionStart(PhysicsComponent *comp) {
    if (comp->getGameObject()->name.compare("House") == 0 ){
        deleteGameObject();
    }
    
}

void FireBallController::onCollisionEnd(PhysicsComponent *comp) {
    
}

void FireBallController::setVelocity(float i_rotation) {
    this->velocity = glm::rotateZ(glm::vec3(0,speed,0), glm::radians(i_rotation));
}

float FireBallController::getSpeed() {
    return this->speed;
}

void FireBallController::update(float deltaTime) {

    time_elapsed += deltaTime;
    if (time_elapsed >= life_time) {
        deleteGameObject();
    }
}


