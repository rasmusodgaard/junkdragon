//
//  PlayingState.hpp
//  SRE
//
//  Created by John O'Donnell
//


#pragma once

#include <string>
#include <map>
#include "GameState.hpp"
#include "sre/SpriteAtlas.hpp"
#include "Level.hpp"

#define F_PHYSICS_TIMESTEP              0.3f
#define INT_WALL_THICKNESS             50
#define INT_HOUSE_COL_WIDTH           100
#define INT_HOUSE_COL_HEIGHT           80

#define INT_DRAGON_SCALE                3
#define INT_BACKGROUND_RESOLUTION      50
#define INT_BACKGROUND_STARTPOS     -2000
#define INT_BACKGROUND_SIZE          4000
#define F_ROTATION_NORTH                0.0f
#define F_FIREBALL_OFFSET             120.0f
#define F_GAME_LENGTH                  60.0f

// Layers
#define U_GROUND_LAYER                 1
#define U_POWERUP_LAYER                2
#define U_FIREBALL_LAYER               3
#define U_DRAGON_LAYER                 4

class SingleVarGuiComponent;
class Command;

class PlayingState : public GameState {
    public:
        void enterState() override;
        void exitState() override;
        void update(float time) override;
        void render( sre::RenderPass &renderPass ) override;
        bool onKey(SDL_Event &event) override;

        void setNextLevelToLoad(std::string next_level);

        bool checkGameOver();

        std::string next_level_to_load = "_";

        // Gameobject existance
        void createDragon( glm::vec2 starting_position );
        void createFireBall( );
        void createHouse( glm::vec2 pos );
        void createPickUp( glm::vec2 pos, sre::Sprite pickUpSprite, Command cmd );
        void createWalls(glm::vec2 dimensions, int thickness);
        void createCamera() override;
        void houseBurnedDown();
        void buildGUI();
        void addFuelToDragon();
        void removeFuelFromDragon();
        void fasterDragon();
        void setScore(float score);
        std::shared_ptr<GameObject> guiObj;

    private:   
        const float physicsScale = 100;
        
        std::shared_ptr<Level> current_level;
        bool    burnination_has_begun;
        float   time_elapsed;
        float   time_remaining;
        bool    game_over;
        int     n_houses;
        int     score = 0;
        int     best_score = score;

        std::shared_ptr<sre::SpriteAtlas> spriteAtlas;

        std::shared_ptr<GameObject> dragonObj;

        std::shared_ptr<SingleVarGuiComponent> timeTrackComp;
        std::shared_ptr<SingleVarGuiComponent> scoreTrackComp;
        std::shared_ptr<SingleVarGuiComponent> houseTrackComp;
        

        // Walls
        std::shared_ptr<GameObject> wallTop;
        std::shared_ptr<GameObject> wallBottom;
        std::shared_ptr<GameObject> wallLeft;
        std::shared_ptr<GameObject> wallRight;
    
    
        std::map<std::string, Command> command_map;
};
