//
//  PickUpComponent.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 21/11/2018.
//

#pragma once
#include "Component.hpp"

class PhysicsComponent;



class PickUpComponent : public Component {
public:
    explicit PickUpComponent(GameObject *gameObject);
    
    void update(float deltaTime) override;
    
    void onCollisionStart(PhysicsComponent *comp) override;

private:
 
    
    
    
    
};
