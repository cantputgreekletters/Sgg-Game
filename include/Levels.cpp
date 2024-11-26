#include "include/Levels.h"
#include "include/GameState.h"
#include "include/MyGraphics.h"
//Level

Level::Level(GameState * gm_state, unsigned int level_index, graphics::Brush bg_brush)
{
    Level::game_state = gm_state;
    Level::lvl_idx = level_index;
    Level::background_brush = bg_brush;
    gm_state->ChangeBackground(bg_brush);
}

//MainMenu

MainMenu::MainMenu(GameState * gm_state, graphics::Brush bg_brush) : Level(gm_state, 0, bg_brush)
{
    std::cout << "Entering MainMenu constructor..." << std::endl;
    StartButton = new Button(game_state, "Start", GetCommand());
    Vector2<float> pos = game_state->GetScreenCenter();
    StartButton->ChangePos(pos);
    QuitButton = new Button(game_state, "Quit", my_graphics::EndGame);
    QuitButton->ChangePos(pos + Vector2<float>(0, 340));
    background_brush.fill_color[0] = 0.f;
    background_brush.fill_color[1] = .3f;
    background_brush.fill_color[2] = .6f;
    std::cout << "Exiting MainMenu constructor..." << std::endl;
}
MainMenu::~MainMenu() // important
{
    delete StartButton;
    delete QuitButton;
    std::cout << "Deleting main menu" << std::endl;
}
void MainMenu::Update()
{
    StartButton->Update();
    QuitButton->Update();
    if (start)
    {
        game_state->ChangeLevel(1);
        start = false;
    }
}
void MainMenu::Draw()
{
    StartButton->Draw();
    QuitButton->Draw();
}

//LevelManager

Level * LevelManager::SelectLevel(unsigned int level_idx)
{
    std::cout << "Selecting Level with index " << level_idx << "..." << std::endl;
    Level* lvl;
    graphics::Brush level_brush;
    //defaults
    level_brush.fill_color[0] = 0.1f;
    level_brush.fill_color[1] = 0.2f;
    level_brush.fill_color[2] = 0.7f;
    //
    switch (level_idx)
    {
    case 0:
        level_brush.fill_color[0] = 0.1f;
        level_brush.fill_color[1] = 0.2f;
        level_brush.fill_color[2] = 0.7f;
        std::cout << "Making main menu" << std::endl;
        lvl = new MainMenu(Game_State, level_brush);
        std::cout << "Made main menu" << std::endl;
        std::cout << level_idx << std::endl;
        break;
    case 1:
        level_brush.fill_color[0] = 0.0f;
        level_brush.fill_color[1] = 0.7f;
        level_brush.fill_color[2] = 0.2f;
        std::cout <<"Making Game Level..." << std::endl;
        lvl = new GameLevel(Game_State, level_brush);
        break;
    default:
        lvl = new MainMenu(Game_State, level_brush);
        break;
    }
    std::cout << "Returning Level.." << std::endl;
    return lvl;
}

//GameLevel

GameLevel::GameLevel(GameState * gm_state, graphics::Brush bg_brush) : Level(gm_state,1, bg_brush)
{
    Player = new PlayerObject(gm_state);
    EnemySpawner = new Spawner(game_state, Player);
    MainMenuButton = new Button(game_state, "Return", GetCommand());

    MainMenuButton->ChangePos(Vector2<float>(150,150));

}
GameLevel::~GameLevel()
{
    delete Player;
    delete EnemySpawner;
    delete MainMenuButton;
}
void GameLevel::Update()
{
    Player->Update();
    EnemySpawner->Update();
    MainMenuButton->Update();

    if(return_tomm)
    {
        game_state->ChangeLevel(0);
    }
}
void GameLevel::Draw()
{
    Player->Draw();
    EnemySpawner->Draw();
    MainMenuButton->Draw();
}