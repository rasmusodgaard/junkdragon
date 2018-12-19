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
    ImVec2 iWinSize(winSize.x*this->size.x, winSize.y* this->size.y);

    // TODO make GUI position flexible
    ImVec2 pos (winSize.x*this->pos.x, winSize.y * this->pos.y ); // (1.0f - this->size.y)
    auto cond = ImGuiCond_Always;

    ImGui::SetNextWindowPos(pos, cond);
    ImGui::SetNextWindowSize(iWinSize, cond);
    ImGui::Begin(this->label.c_str(), open, flags);
    
    ImGui::Text( "%s: %0.2f", this->label.c_str(), this->val );

    ImVec2 uv0(0,1); // flip y axis coordinates
    ImVec2 uv1(1,0);

    ImGui::End();
}

void FloatTrackComponent::init( std::string label, float val, glm::vec2 pos, glm::vec2 size ) {
    this->label = label;
    this->val = val;
    this->pos = pos;
    this->size = size;
}

void FloatTrackComponent::setVal( float val ) {
    this->val = val;
}