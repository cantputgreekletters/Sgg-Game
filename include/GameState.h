#if !defined(__GAMESTATE_H__)
#define __GAMESTATE_H__
#include "sgg/graphics.h"
#include "include/MyMath.h"
#include "include/GameObjects.h"
#include "include/Levels.h"
class Level; // from include/Levels.h
class MainMenu; // from include/Levels.h
/*
Η κλάση GameState από την οποία θα πρέπει να έχετε ένα και μοναδικό στιγμιότυπο στην εφαρμογή σας:
α) φυλάει δεδομένα για τη ροή και την κατάσταση του παιχνιδιού (π.χ. σε πιο level είμαστε, τα διαθέσιμα
levels, στατιστικά, σκορ, κλπ.)
β) διαθέτει τις βασικές μεθόδους draw, init και update που καλούν τις αντίστοιχες έμμεσα ή άμεσα για
οποιοδήποτε αντικείμενο λειτουργεί μέσα στο παιχνίδι σας.
γ) είναι υπεύθυνη για το ξεκίνημα, την εναλλαγή επιπέδων (πιστών) και τον τερματισμό του παιχνιδιού.
δ) παρέχει ένα κεντρικό σημείο πρόσβασης για να εντοπιστούν στοιχεία του παιχνιδιού (π.χ.
GameState::getPlayer())
*/

class LevelManager;

class GameState{ //init is missing
    private:
        unsigned int difficulty = 1;
        unsigned int Score = 0;
        unsigned int _max_score = 30000; //so it cant pass the memory limit :)
        unsigned int HighScore = 0;
        graphics::MouseState GameMouse;
        int SCREEN_WIDTH = 1920;
        int SCREEN_HEIGHT = 1080;
        LevelManager * levelmanager;
        bool Run = true;
    public:
    void AttatchLevelManager(LevelManager* lvlmanager)
    {
        levelmanager = lvlmanager;
    }
    void ChangeLevel(unsigned int idx);
    void Draw()
    {
    }
    void Update()
    {
        graphics::getMouseState(GameMouse);
        if(! Run)
        {
            graphics::stopMessageLoop();
        }
    }
    //Setters
    void SizeFunc(int new_w, int new_h)
    {
        SCREEN_WIDTH = new_w;
        SCREEN_HEIGHT = new_h;
    }
    void ChangeBackground(graphics::Brush Br)
    {
        graphics::setWindowBackground(Br);
    }
    //Getters
    Vector2<int> GetMouseGlobalCords()
    {
        int pos_x = (int) GameMouse.cur_pos_x * 1920 / SCREEN_WIDTH; // 1920 = max canvas width
        int pos_y = (int) GameMouse.cur_pos_y * 1080 / SCREEN_HEIGHT; // 1080 = max canvas height
        return Vector2<int>(pos_x, pos_y);
    }
    graphics::MouseState GetMouseState(){return GameMouse;};
    int GetScreenWidth(){return SCREEN_WIDTH;};
    int GetScreenHeight(){return SCREEN_HEIGHT;};
    Vector2<float> GetScreenCenter()
    {
        Vector2<float> center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        return center;
    }
    
};


#endif // __GAMESTATE_H__
