#include <SDL_events.h>
#include <iostream>
#include "FireBallController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "JunkDragonGame.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

FireBallController::FireBallController(GameObject *gameObject) : Component(gameObject) {

    speed = 7.0f;
    time_elapsed = 0.0f;
    life_time = 0.6f;
    drag = 0.99f;
}

void FireBallController::onCollisionStart(PhysicsComponent *comp) {
    //deleteGameObject();
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
    
    // Move the fireball
    //this->getGameObject()->setPosition( this->getGameObject()->getPosition() + velocity * deltaTime );

    //velocity = velocity * drag;

    time_elapsed += deltaTime;
    if (time_elapsed >= life_time) {
        //std::cout << this->getGameObject()->getPosition().x << " " << this->getGameObject()->getPosition().y << std::endl;
        deleteGameObject();
    }
}


