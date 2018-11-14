#include <SDL_events.h>
#include <iostream>
#include "DragonController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "JunkDragonGame.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

DragonController::DragonController(GameObject *gameObject) : Component(gameObject) {
    // initiate dragon physics
    CW_rotation = true;
    speed = 300.0f;
    rotation_speed = 2.0f;
    
    // fire breathing parameters
    breathing_fire = false;
    last_fire_ball = 0.0f;
    cool_down = 0.08f;

}

bool DragonController::onKey(SDL_Event &event) {
    if (event.key.keysym.sym == SDLK_LEFT) {
        if (event.type == SDL_KEYDOWN) {
            CW_rotation = false;
        }
    }

    if (event.key.keysym.sym == SDLK_RIGHT) {
        if (event.type == SDL_KEYDOWN) {
            CW_rotation = true;
        }
    }

    if (event.key.keysym.sym == SDLK_SPACE) {
        if (event.type == SDL_KEYDOWN) {
            this->breathing_fire = true;
        }
        if (event.type == SDL_KEYUP) {
            this->breathing_fire = false;
        }
    }

    return false;
}

void DragonController::onCollisionStart(PhysicsComponent *comp) {

}

void DragonController::onCollisionEnd(PhysicsComponent *comp) {
    
}

void DragonController::breathe_fire() {
    JunkDragonGame::instance->createFireBall();
}

void DragonController::update(float deltaTime) {
    
    glm::vec2 position = this->getGameObject()->getPosition();
    float rotation = this->getGameObject()->getRotation();
    float magnitude = deltaTime * speed;
    glm::vec2 velocity = glm::rotateZ(glm::vec3(0,magnitude,0), glm::radians(rotation));

    if(CW_rotation) {
         this->getGameObject()->setRotation(rotation - rotation_speed);
    } else {
        this->getGameObject()->setRotation(rotation + rotation_speed);
    }
    
    // Move the head
    this->getGameObject()->setPosition( position + velocity );

    if(breathing_fire){
        if(last_fire_ball > cool_down ) {
            last_fire_ball = 0.0f;
            breathe_fire();
        }
        
    }

    last_fire_ball += deltaTime;

}

