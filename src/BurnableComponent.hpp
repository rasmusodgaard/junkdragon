//
//  BurnableComponent.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//

#pragma once
#include "Component.hpp"
#include "Command.hpp"

#define F_TIME_TO_BURN  6.0f
#define F_TIME_TO_SINGE 3.0f

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
    void setBurnCmd( Command burn_cmd );
    
private:
    Command burn_cmd;
    std::shared_ptr<AnimationControllerComponent> animationControllerComponent;
    bool onFire;
    bool destroyed;
    float life_time;
    float singed_time;

    
    
    
};

