//
//  SingleVarGuiComponent.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "SingleVarGuiComponent.hpp"
#include "sre/Renderer.hpp"
#include "JunkDragonGame.hpp"
#include <iostream>

SingleVarGuiComponent::SingleVarGuiComponent(GameObject *gameObject)
    : Component(gameObject) {

    }

void SingleVarGuiComponent::onGui() {
    float gui_height = 0.1f;
    
    auto r = sre::Renderer::instance;

    auto flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove;
    bool* open = nullptr;
    
    auto winSize = r->getWindowSize();
    ImVec2 iWinSize(winSize.x*this->size.x, winSize.y* this->size.y);

    // TODO make GUI position flexible
    ImVec2 pos (winSize.x*this->pos.x, winSize.y * this->pos.y ); // (1.0f - this->size.y)
    auto cond = ImGuiCond_Always;

    ImGui::SetNextWindowPos(pos, cond);
    ImGui::SetNextWindowSize(iWinSize, cond);
    ImGui::Begin(this->label.c_str(), open, flags);
    
    if(this->data_type == FLOAT) {
        ImGui::Text( "%s: %0.2f", this->label.c_str(), this->f_val );
    } else {
        ImGui::Text( "%s: %d", this->label.c_str(), this->i_val );
    }

    ImVec2 uv0(0,1); // flip y axis coordinates
    ImVec2 uv1(1,0);

    ImGui::End();
}

void SingleVarGuiComponent::init( std::string label, float f_val, glm::vec2 pos, glm::vec2 size ) {
    this->label     = label;
    this->f_val     = f_val;
    this->pos       = pos;
    this->size      = size;
    this->data_type = FLOAT;
}

void SingleVarGuiComponent::setVal( float f_val ) {
    if(this->data_type == FLOAT) {
        this->f_val = f_val;
    } else {
        std::cerr << "GUI Element " << this->label << "set to INTEGER" << std::endl;
    }
}

void SingleVarGuiComponent::init( std::string label, int i_val, glm::vec2 pos, glm::vec2 size ) {
    this->label     = label;
    this->i_val     = i_val;
    this->pos       = pos;
    this->size      = size;
    this->data_type = INTEGER;

}

void SingleVarGuiComponent::setVal( int i_val ) {
    if(this->data_type == INTEGER) {
        this->i_val = i_val;
    } else {
        std::cerr << "GUI Element " << this->label << "set to FLOAT" << std::endl;
    }
}