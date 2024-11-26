#if !defined(__LEVELS_H__)
#define __LEVELS_H__

#include "sgg/graphics.h"
#include "include/GameObjects.h"
#include "include/MyGraphics.h"
#include <iostream>

class GameState;

class Level
{
    protected:
        GameState * game_state;
        unsigned int lvl_idx;
        graphics::Brush background_brush;

    public:
        Level(GameState * gm_state, unsigned int level_index, graphics::Brush bg_brush);
        
        virtual ~Level()
        {
            
        }
        virtual void Draw(){}
        virtual void Update(){}
};

class Button;

class MainMenu : public Level
{
    private:
        Button * StartButton;
        Button * QuitButton;
        bool start = false;
        
        void StartButtonCommand()
        {
            start = true;
        }
        
    public:
        MainMenu(GameState * gm_state, graphics::Brush bg_brush);

        ~MainMenu();

        virtual void Draw();
        virtual void Update();
        std::function<void()> GetCommand() 
        {
            return [this]() { 
                StartButtonCommand(); 
            };
    }
};

class PlayerObject;
class Spawner;

class GameLevel : public Level
{
    private:
        PlayerObject* Player;
        Spawner * EnemySpawner;
        Button * MainMenuButton;
        bool return_tomm = false;
        void ButtonCommand()
        {
            return_tomm = true;
        }
    public:
        GameLevel(GameState * gm_state, graphics::Brush bg_brush);
        ~GameLevel();
        virtual void Update();
        virtual void Draw();

        std::function<void()> GetCommand() 
        {
            return [this]() { 
                ButtonCommand(); 
            };
        }
};

class LevelManager
{
    private:
        GameState * Game_State;
        unsigned int current_level_idx = 0;
        Level* current_level;
        void UnloadLevel()
        {
            if (! current_level)
            {
                return;
            }
            delete current_level;
            current_level = NULL;
        }
        Level * SelectLevel(unsigned int level_idx);
    public:

        LevelManager(GameState* gs)
        {
            Game_State = gs;
        }      

        void LoadLevel(unsigned int level_idx)
        {
            std::cout << "Unloading level..." << std::endl;
            UnloadLevel();
            std::cout << "Unloaded Level and selecting level..." << std::endl;
            current_level = SelectLevel(level_idx);
            if(current_level)
            {
                std::cout << "Loaded level with index" << level_idx << std::endl;
            } else{
                std::cout << "Did not load level with index" << level_idx << std::endl;
            }
        }
        void Update()
        {
            if(current_level)
            {
                current_level->Update();
            }
        }
        void Draw()
        {
            if(current_level)
            {
                current_level->Draw();
            }
        }

};

#endif // __LEVELS_H__
