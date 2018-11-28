//
//  BurnableComponent.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//

#pragma once
#include "Component.hpp"

class PhysicsComponent;
class AnimationControllerComponent;

class BurnableComponent : public Component {
public:
    explicit BurnableComponent(GameObject *gameObject);
    
    void SetAnimationControllerComponent(std::shared_ptr<AnimationControllerComponent> aC);

    void update(float deltaTime) override;
    
    void onCollisionStart(PhysicsComponent *comp) override;
    void extinguishFire ();
    void burnedDown();

    
private:

    std::shared_ptr<AnimationControllerComponent> animationControllerComponent;
    bool onFire;
    float life_time;
    float singed_time;

    
    
    
};

