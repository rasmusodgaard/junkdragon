//
//  FloatTrackComponent.cpp
//  SRE
//
//  Created by John O'Donnell
//

#pragma once

#include "Component.hpp"
#include <string>

class FloatTrackComponent : public Component {
    public:
        explicit FloatTrackComponent(GameObject *gameObject);

        void onGui() override;

        void init(std::string label, float val, glm::vec2 pos, glm::vec2 size);
        void setVal(float val);

    private:
        std::string  label;
        float          val;
        glm::vec2      pos;
        glm::vec2     size;
};