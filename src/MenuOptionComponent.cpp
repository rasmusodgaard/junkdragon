//
//  MenuOptionComponent.cpp
//  SRE
//
//  Created by Rasmus Odgaard on 21/11/2018.
//

#include "sre/Renderer.hpp"
#include "MenuOptionComponent.hpp"
#include "JunkDragonGame.hpp"

MenuOptionComponent::MenuOptionComponent(GameObject *gameObject) : Component(gameObject)
{
    // TODO what does a button need?
    play_pressed = false;
}

void MenuOptionComponent::update(float deltaTime){
    
}

void MenuOptionComponent::playPressed() {
    // JunkDragonGame::instance->startTheGame();
}

void MenuOptionComponent::settingsPressed() {

}

void MenuOptionComponent::onGui() {
    auto r = sre::Renderer::instance;

    auto flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove;
    bool* open = nullptr;

    ImVec2 imageButtonSize(322,100);
    auto win_size = r->getWindowSize();
    ImVec2 iWinSize(348, 125);

    ImVec2 pos ((win_size.x - iWinSize.x)/2.0f, 3.0f*win_size.y/5.0f);
    auto cond = ImGuiCond_Always;
    ImGui::SetNextWindowPos(pos, cond);
    ImGui::SetNextWindowSize(iWinSize, cond);
    ImGui::Begin("", open, flags);

    static auto playTex = sre::Texture::create()
        .withFile("play.png")
        .withFilterSampling(false)
        .build();
    // static auto settingsTex = sre::Texture::create()
    //     .withFile("play_hatch.png")
    //     .withFilterSampling(false)
    //     .build();

    void* playId = playTex->getNativeTexturePtr();
    // void* settingsId = settingsTex->getNativeTexturePtr();

    ImVec2 uv0(0,1);
    ImVec2 uv1(1,0);

    if(ImGui::ImageButton(playId, imageButtonSize, uv0, uv1)){
        play_pressed = true;
    }
    // if(ImGui::ImageButton(settingsId, imageButtonSize, uv0, uv1)){
    //     settingsPressed();
    // }
    ImGui::End();
}