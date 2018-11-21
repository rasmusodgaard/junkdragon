#pragma once

#include "Component.hpp"
#include "sre/Sprite.hpp"
#include "SpriteComponent.hpp"
#include <string>

struct AnimationState {
    std::string label;
    float animationTime;
    std::vector <sre::Sprite> sprites;
};

class AnimationControllerComponent : public Component {
    public:
        AnimationControllerComponent(GameObject *gameObject);

        void addState(std::string label, float animationTime, std::vector<sre::Sprite>);

        int setState(std::string label);

        // float getAnimationTimeForState(std::string label) const; // time between animations (s)
        // void setAnimationTimeForState(float animationTime);

        void setScale(glm::vec2 i_scale);

        void printa();

        void update(float deltaTime) override;

        AnimationState* findState(std::string label);
    
    private:
        std::vector<AnimationState> aStates;

        AnimationState *currState;

        float time;
        int spriteIndex;
        glm::vec2 sprite_scale;

};