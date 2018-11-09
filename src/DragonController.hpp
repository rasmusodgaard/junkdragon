#pragma once

#include "Component.hpp"

class DragonController : public Component {
    public:
        explicit DragonController(GameObject *gameObject);

        bool onKey(SDL_Event &event) override;

        void onCollisionStart(PhysicsComponent *comp) override;

        void onCollisionEnd(PhysicsComponent *comp) override;

        void update(float deltaTime) override;

    private:
        std::shared_ptr<PhysicsComponent> physicsComponent;

        bool CW_rotation;

        float speed;
        float rotation_speed;
};