//
//  BurnableComponent.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 14/11/2018.
//

#pragma once
#include "Component.hpp"

class PhysicsComponent;

class BurnableComponent : public Component {
public:
    explicit BurnableComponent(GameObject *gameObject);
    
    void update(float deltaTime) override;
    
    void onCollisionStart(PhysicsComponent *comp) override;
    void extinguishFire ();
    void burnedDown();
private:
    bool onFire;
    float time_elapsed;
    float life_time;

    
    
    
};

