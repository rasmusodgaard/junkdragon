#pragma once

#include "Component.hpp"
#include <string>

class FloatTrackComponent : public Component {
    public:
        explicit FloatTrackComponent(GameObject *gameObject);

        void onGui() override;

        void setLabel(std::string i_label);
        void setVal(float i_val);

    private:
        std::string label;
        float val;
};