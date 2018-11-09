#pragma once

#include "Component.hpp"
#include "sre/Sprite.hpp"
#include "SpriteComponent.hpp"

class SpriteAnimationComponent : public Component {
    public:
        SpriteAnimationComponent(GameObject *gameObject);

        void setSprites(std::vector<sre::Sprite> sprites); // sprite sequence

        void update(float deltaTime) override;

        float getAnimationTime() const; // time between animations (s)

        void setAnimationTime(float animationTime);

        void setScale(glm::vec2 i_scale);
    
    private:
        float animationTime = 0.300f;
        std::vector<sre::Sprite> sprites;
        float time = 0;
        int spriteIndex = 0;
        glm::vec2 sprite_scale = {1,1};

};