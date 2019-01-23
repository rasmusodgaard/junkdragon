//
//  AnimationControllerComponent.hpp
//  SRE
//
//  Created by John O'Donnell
//

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

        void setScale(glm::vec2 i_scale);

        void print();

        void update(float deltaTime) override;

        void setLayer( uint16_t orderInBatch );
    
    
        AnimationState* findState(std::string label);
    
    private:
        // Vector of animation states
        std::vector<AnimationState> aStates;

        // Parameters of current animation state
        AnimationState *currState;
        float time = 0.0f;
        int spriteIndex = 0;

        // Applied when set. Common to all animation states in this component instance.
        uint16_t orderInBatch = 1;
        glm::vec2 sprite_scale;

};
