//
//  GameState.hpp
//  SRE
//

#pragma once

#include <string>
#include "GameObject.hpp"
#include "BackgroundComponent.hpp"

class CameraFollow;

class GameState {
    public:
        virtual void enterState();
        virtual void exitState();
        virtual void update(float time);
        virtual void render( sre::RenderPass &renderPass );
        virtual bool onKey(SDL_Event &event);  
        virtual void createCamera();
        std::shared_ptr<GameObject> createGameObject();
 
        std::string name = "_";

        std::shared_ptr<CameraFollow> camera;
        std::shared_ptr<GameObject> camObj;

        BackgroundComponent backgroundComponent;


    protected:
        std::vector<std::shared_ptr<GameObject>> sceneObjects;
        bool isLoaded = false;

    private:
        friend class JunkDragonGame;
        

};