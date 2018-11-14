#pragma once

#include "Component.hpp"

class FireBallController : public Component {
    public:
        explicit FireBallController(GameObject *gameObject);

        void onCollisionStart(PhysicsComponent *comp) override;

        void onCollisionEnd(PhysicsComponent *comp) override;

        void setVelocity(float i_rotation);

        void update(float deltaTime) override;


    private:
        std::shared_ptr<PhysicsComponent> physicsComponent;

        float speed;
        float time_elapsed;
        float life_time;
        float drag;

        glm::vec2 velocity = {0,0};
};
