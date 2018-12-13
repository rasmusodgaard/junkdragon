//
//  FireBallControllerComponent.hpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once
#include "Component.hpp"

#define F_FIREBALL_SPEED   20.0f
#define F_TIME_ELAPSED      0.0f
#define F_LIFE_TIME         0.6f
#define F_DRAG              0.99f

class FireBallController : public Component {
    public:
        explicit FireBallController(GameObject *gameObject);

        void onCollisionStart(PhysicsComponent *comp) override;

        void onCollisionEnd(PhysicsComponent *comp) override;

        void setVelocity(float i_rotation);
        float getSpeed();

        void update(float deltaTime) override;


    private:
        std::shared_ptr<PhysicsComponent> physicsComponent;

        float speed;
        float time_elapsed;
        float life_time;
        float drag;

        glm::vec2 velocity = {0,0};
};
