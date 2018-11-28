//
//  PickUpComponent.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 21/11/2018.
//

#pragma once
#include "Component.hpp"
#include "Command.hpp"

class PhysicsComponent;


class PickUpComponent : public Component {
public:
    explicit PickUpComponent(GameObject *gameObject);
    Command cmd;
    void update(float deltaTime) override;
    
    void onCollisionStart(PhysicsComponent *comp) override;
    
    void SetCommand (Command _cmd);
private:
 
    
    
    
    
};
