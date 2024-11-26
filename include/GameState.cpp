#include "include/GameState.h"
#include "include/Levels.h"

void GameState::ChangeLevel(unsigned int idx)
    {
        levelmanager->LoadLevel(idx);
    }