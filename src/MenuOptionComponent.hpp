//
//  MenuOptionComponent.hpp
//  SRE
//
//  Created by Rasmus Odgaard on 21/11/2018.
//

#pragma once
#include "Component.hpp"
#include <string>

class MenuOptionComponent : public Component {
public:
    explicit MenuOptionComponent(GameObject *gameObject);
    void update(float deltaTime) override;

    void playPressed();
    void settingsPressed();
    void onGui() override;

    std::string name = "_";
    bool play_pressed;

private:    
};
