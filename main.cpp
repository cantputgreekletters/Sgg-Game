#include <string>
#include "sgg/graphics.h"
#include "include/GameState.h"
#include "include/MyGraphics.h"
#include "include/GameObjects.h"
#include <iostream>
// The custom callback function that the library calls 
// to check for and set the current application state.
const std::string img = "assets\\boy2.png";
GameState Game_State;
LevelManager * Level_Manager;
float DeltaTime = 0.f;

void update(float ms)
{
    DeltaTime = graphics::getDeltaTime();
    Game_State.Update();
    Level_Manager->Update();
}

static void resize(int width, int height)
{
    Game_State.SizeFunc(width, height);
}
 
// The window content drawing function.
void draw()
{
    Game_State.Draw();
    Level_Manager->Draw();
    graphics::resetPose();
}
int main()
{
    std::cout << "Starting Game..." << std::endl;
    graphics::createWindow(1200, 600, "Hello World");
    Game_State.SizeFunc(1200,600);
    Level_Manager = new LevelManager(&Game_State);
    std::cout << "Attatching Level Manager.." << std::endl;
    Game_State.AttatchLevelManager(Level_Manager);
    std::cout << "Setting Level to main menu..." << std::endl;
    Game_State.ChangeLevel(0);
    std::cout << "Setting functions.." << std::endl;
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    graphics::setResizeFunction(resize);
    graphics::setCanvasSize(1920, 1080);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_STRETCH);
    
    graphics::Brush br;
    br.fill_color[0] = 0.5f;
    br.fill_color[1] = 0.7f;
    br.fill_color[2] = 0.9f;
    graphics::setWindowBackground(br);
 
    graphics::setFont("assets\\Lato-Regular.ttf");
    std::cout << "Starting message loop.." << std::endl;
    graphics::startMessageLoop();
    return 0;
}
