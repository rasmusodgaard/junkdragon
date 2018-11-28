//
//  FloatTrackComponent.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "FloatTrackComponent.hpp"
#include "sre/Renderer.hpp"
#include "JunkDragonGame.hpp"

FloatTrackComponent::FloatTrackComponent(GameObject *gameObject)
    : Component(gameObject) {

    }

void FloatTrackComponent::onGui() {
    float gui_height = 0.1f;
    
    auto r = sre::Renderer::instance;

    auto flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove;
    bool* open = nullptr;
    
    auto winSize = r->getWindowSize();
    ImVec2 iWinSize(winSize.x*this->width, winSize.y* this->height);

    // TODO make GUI position flexible
    ImVec2 pos (winSize.x*this->x_pos, winSize.y * (1.0f - this->height) );
    auto cond = ImGuiCond_Always;

    ImGui::SetNextWindowPos(pos, cond);
    ImGui::SetNextWindowSize(iWinSize, cond);
    ImGui::Begin(this->label.c_str(), open, flags);
    ImGui::Text( "%s: %0.2f", this->label.c_str(), this->val );

    ImVec2 uv0(0,1); // flip y axis coordinates
    ImVec2 uv1(1,0);

    ImGui::End();
}

void FloatTrackComponent::setLabel( std::string i_label ) {
    this->label = i_label;
}

void FloatTrackComponent::setVal( float i_val ) {
    this->val = i_val;
}

void FloatTrackComponent::setSize(float i_width, float i_height) {
    this->width = i_width;
    this->height = i_height;
}

void FloatTrackComponent::setPos(float i_x, float i_y) {
    this->x_pos = i_x;
    this->y_pos = i_y;
}