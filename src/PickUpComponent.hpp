//
//  PickUpComponent.hpp
//  SRE
//

#pragma once
#include "Component.hpp"
#include "Command.hpp"

#define F_PICKEDUP      false

class PhysicsComponent;


class PickUpComponent : public Component {
public:
    explicit PickUpComponent(GameObject *gameObject);
    Command cmd;
    void update(float deltaTime) override;
    
    void onCollisionStart(PhysicsComponent *comp) override;
    
    void SetCommand (Command _cmd);
private:
    bool pickedUp;
    
    
    
    
};
