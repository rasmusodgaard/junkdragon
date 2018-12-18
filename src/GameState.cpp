//
//  Component.cpp
//  SRE
//
//  Created by John O'Donnell
//

#include "JunkDragonGame.hpp"
#include "GameState.hpp"

void GameState::enterState() {

}

void GameState::exitState() {

}

void GameState::update(float time) {

}

void GameState::render() {

}

bool GameState::onKey(SDL_Event &event) {
    return false;
}

void GameState::createCamera() {
    
}

std::shared_ptr<GameObject> GameState::createGameObject() {
    auto obj = std::shared_ptr<GameObject>(new GameObject());
    sceneObjects.push_back(obj);
    return obj;
}

