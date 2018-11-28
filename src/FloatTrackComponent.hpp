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

        void setLabel(std::string i_label);
        void setVal(float i_val);
        void setSize(float i_width, float i_height);
        void setPos(float i_x, float i_y);

    private:
        std::string label;
        float val;

        float width;
        float height;
        float x_pos;
        float y_pos;
};