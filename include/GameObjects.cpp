#include "include/GameObjects.h"
#include "include/GameState.h"

#include <stdio.h>

//PlayerObject
PlayerObject::PlayerObject(GameState * gs) : GameObject(gs, "assets/player.png")
{
    Brush.outline_opacity = 0.f;
    rectangle.ChangePos(m_state->GetScreenCenter());
    Arrow = new PlayerArrow(gs);
};

//Button

void Button::CheckIfHighlighted()
{
    Vector2<int> mouse_cords = game_state->GetMouseGlobalCords(); 
    graphics::MouseState mouse = game_state->GetMouseState();
    is_highlighted = rectangle.IsHighlightedByMouse(mouse_cords);
    if (mouse.button_left_pressed && is_highlighted)
    {
        command();
    }
}

void Button::Update()
{
    CheckIfHighlighted();
}