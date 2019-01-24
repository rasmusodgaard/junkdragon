//
//  SingleVarGuiComponent.cpp
//  SRE
//

#pragma once

#include "Component.hpp"
#include <string>

#define INTEGER     0
#define FLOAT       1

class SingleVarGuiComponent : public Component {
    public:
        explicit SingleVarGuiComponent(GameObject *gameObject);

        void onGui() override;

        void init(std::string label, float val, glm::vec2 pos, glm::vec2 size);
        void init(std::string label, int val, glm::vec2 pos, glm::vec2 size);

        void setVal(float val);
        void setVal(int val);

    private:
        std::string label;
        float       f_val;
        int         i_val;
        glm::vec2   pos;
        glm::vec2   size;
        bool        data_type = INTEGER;
};