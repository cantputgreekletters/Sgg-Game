#if !defined(__GAMEOBJECTS_H__)
#define __GAMEOBJECTS_H__

#include "sgg/graphics.h"
#include "include/MyGraphics.h"
#include "include/MyMath.h"
#include "include/GameState.h"
#include <string>
#include <iostream>

class GameState;

class Rect
{
    private:
        float width;
        float height;
        bool DEBUG;
    public:
        Vector2<float> position;
        Rect() : position(200.f, 200.f), width(200.f), height(200.f), DEBUG(false){}
        Rect(Vector2<float> pos, float rect_width = 200.0f, float rect_height = 200.0f)
        {
            position = pos;
            SetWidth(rect_width);
            SetHeight(rect_height);
        }

        void Draw(graphics::Brush brush)
        {
            if(DEBUG)
            {
                graphics::Brush dbg_brush;
                dbg_brush.fill_color[0] = 1.f;
                dbg_brush.fill_color[1] = 0.f;
                dbg_brush.fill_color[2] = 0.f;
                my_graphics::DrawVectorLine(GetTopLeftCorner(), GetBottomRightCorner(), dbg_brush);
            }
            graphics::drawRect(position.x, position.y, width, height, brush);
        }
        void ChangePos(Vector2<float> new_pos)
        {
            position = new_pos;
        }
        void IncrementX(float step = 1.0f)
        {
            position.x += step;
        }
        void IncrementY(float step = 1.0f)
        {
            position.y += step;
        }
        void EnableDebug()
        {
            DEBUG = true;
        }
        bool IsIn(Vector2<float> obj)
        {
            bool st1 = obj.x >= position.x - width / 2 && obj.x <= position.x + width / 2;
            bool st2 = obj.y >= position.y - height / 2 && obj.y <= position.y + height / 2;
            //bool st1 = obj.x >= (position.x - width / 2) * 100 / my_graphics::GetScreenWidth() && obj.x <= (position.x + width / 2) * 100 / my_graphics::GetScreenWidth();
            //bool st2 = obj.y >= (position.y - height / 2) * 100 / my_graphics::GetScreenHeight() && obj.y <= (position.y + height / 2) * 100 / my_graphics::GetScreenHeight();
            return st1 && st2;
        }
        bool IsIn(Vector2<int> obj)
        {
            bool st1 = obj.x >= position.x - width / 2 && obj.x <= position.x + width / 2;
            bool st2 = obj.y >= position.y - height / 2 && obj.y <= position.y + height / 2;
            return st1 && st2;
        }
        bool IsHighlightedByMouse(Vector2<int> mouse_cords)
        {
            return IsIn(mouse_cords);
        }
        //Setters
        void SetWidth(float num)
        {
            if (num < 0)
            {
                return;
            }
            width = num;
        }
        void SetHeight(float num)
        {
            if (num < 0)
            {
                return;
            }
            height = num;
        }
        //Getters
        float GetPosX()
        {
            return position.x;
        }
        float GetPosY()
        {
            return position.y;
        }
        float GetWidth()
        {
            return width;
        }
        float GetHeight()
        {
            return height;
        }
        Vector2<float> GetPosition()
        {
            return position;
        }
        Vector2<float> GetTopLeftCorner()
        {
            float x;
            float y;
            x = position.x - width / 2;
            y = position.y - height / 2;
            return Vector2<float>(x,y);
        }
        Vector2<float> GetTopRightCorner()
        {
            float x;
            float y;
            x = position.x + width / 2;
            y = position.y - height / 2;
            return Vector2<float>(x,y);
        }
        Vector2<float> GetBottomLeftCorner()
        {
            float x;
            float y;
            x = position.x - width / 2;
            y = position.y + height / 2;
            return Vector2<float>(x,y);
        }
        Vector2<float> GetBottomRightCorner()
        {
            float x;
            float y;
            x = position.x + width / 2;
            y = position.y + height / 2;
            return Vector2<float>(x,y);
        }
};

class GameObject
{
    static int m_next_id;
    /*
    public:        
        virtual void init() {}
        virtual ~GameObject() {}
    */
    private:
        void ChangePos(Vector2<float> pos)
        {
            rectangle.ChangePos(pos);
        }
        void IncrementX(float step = 1.0f)
        {
            rectangle.IncrementX(step);
        }
        void IncrementY(float step = 1.0f)
        {
            rectangle.IncrementY(step);
        }

    protected:
        GameState * m_state;
        bool m_active = true;
        std::string m_name;
        int m_id = 0;
        Rect rectangle;
    public:
        graphics::Brush Brush;
        GameObject(GameState * gs, const std::string img_path)
        {
            m_state = gs;
            Brush.texture = img_path;
        }
        virtual void Draw()
        {
            Brush.outline_opacity = 0.f;
            rectangle.Draw(Brush);
            //Brush.fill_color[0] = 0.5f;
            //Brush.fill_color[1] = 0.0f;
            //Brush.fill_color[2] = 0.0f;
        }
        virtual void Update(float dt) 
        {
            //dk
        }
        bool IsActive()
        {
            return m_active;
        }
        void SetActive(bool a)
        {
            m_active = a;
        }
        

};

class PlayerArrow : public GameObject
{
    private:
        float speed = 2.5f;
        void Move()
        {
            rectangle.position.y -= speed * graphics::getDeltaTime();
        }
    public:
        PlayerArrow(GameState * gs) : GameObject(gs, "assets/arrow.png")
        {
            m_active = false;
            Brush.outline_opacity = 0.f;
        }

        void Shoot(Vector2<float> pos)
        {
            rectangle.ChangePos(pos);
            m_active = true;
        }
        void Die()
        {
            SetActive(false);
        }
        virtual void Draw()
        {
            if(!IsActive())
            {
                return;
            }
            rectangle.Draw(Brush);
        }
        virtual void Update()
        {
            if(!IsActive())
            {
                return;
            }
            if (rectangle.GetPosY() <= -20)
            {
                Die();
            }
            Move();
        }

        Vector2<float> GetPos()
        {
            return rectangle.GetPosition();
        }
};

class PlayerObject : public GameObject{
    private:
        float speed = 1.0f;
        Vector2<int> Direction; // = (0,0)
        PlayerArrow* Arrow;
        void KeyBoardInput() {
            Vector2<int> dir;
            if (graphics::getKeyState(graphics::SCANCODE_A))
            {
                dir.x = -1;
            } else if (graphics::getKeyState(graphics::SCANCODE_D))
            {
                dir.x = 1;
            }
            if (graphics::getKeyState(graphics::SCANCODE_W))
            {
                dir.y = -1;
            } else if (graphics::getKeyState(graphics::SCANCODE_S))
            {
                dir.y = 1;
            }
            Direction = dir;
        }
        void Shoot()
        {
            if(Arrow->IsActive())
            {
                return;
            }
            graphics::playSound("assets/hit1.wav", 1.f); //placeholder
            Arrow->Shoot(rectangle.GetPosition());
        }
        void Move(float dt)
        {
            rectangle.position += Direction * speed * dt;
        }
        void ResetPosIfOutside()
        {
            if (rectangle.GetPosX() < 0)
            {
                rectangle.position.x = 0;
            }else if (rectangle.GetPosX() > 1920)
            {
                rectangle.position.x = 1920;
            }

            if (rectangle.GetPosY() < 0)
            {
                rectangle.position.y = 0;
            }else if (rectangle.GetPosY() > 1080)
            {
                rectangle.position.y = 1080;
            }
        }
    public:
        PlayerObject(GameState * gs);
        ~PlayerObject()
        {
            delete Arrow;
        }
        Vector2<float> GetPos()
        {
            return rectangle.GetPosition();
        }

        void KillArrw()
        {
            Arrow->Die();
        }
        virtual void Update()
        {
            KeyBoardInput();
            if (graphics::getKeyState(graphics::SCANCODE_SPACE))
            {
                Shoot();
            }
            Move(graphics::getDeltaTime());
            ResetPosIfOutside();
            Arrow->Update(); 
        }
        virtual void Draw()
        {
            rectangle.Draw(Brush);
            Arrow->Draw();
        }

        Vector2<float> GetArrowPos()
        {
            return Arrow->GetPos();
        }
};

class Enemy : public GameObject
{
    private:
    PlayerObject * Player;
    Vector2<float> position;
    float speed = 0.3f;
    void Die()
    {
        SetActive(false);
    }
    void Move()
    {
        rectangle.position.y += speed * graphics::getDeltaTime();
    }
    public:
        Enemy(GameState * gs, PlayerObject * player) : GameObject(gs, "assets/enemy.png")
        {
            Player = player;
            m_active = false;
            Brush.outline_opacity = 0.f;
        }
        
        void AssignX(float x)
        {
            rectangle.ChangePos(Vector2<float>(x, rectangle.GetPosY()));
        }
        void ResetState()
        {
            m_active = true;
            rectangle.ChangePos(Vector2<float>(rectangle.GetPosX(), - 50));
        }
        virtual void Update()
        {
            if(! IsActive())
            {
                return;
            }
            Move();
            if (rectangle.IsIn(Player->GetArrowPos()))
            {
                Die();
                Player->KillArrw();
            }
            
            if (rectangle.IsIn(Player->GetPos()) || rectangle.position.y >= 1100)
            {
                Die();
            }
        }
        virtual void Draw()
        {
            if(! IsActive())
            {
                return;
            }
            rectangle.Draw(Brush);
        }
};

class Spawner
{
    private:
        GameState * game_state;
        PlayerObject * Player;
        const int max_enemies = 10;
        const int max_active_enemies = 7;
        bool can_spawn = true;
        unsigned int active_enemies = 0;
        Enemy ** enemy_container = new Enemy*[max_enemies];
        void MakeEnemies()
        {
            for (int i = 0; i < max_enemies; i++)
            {
                enemy_container[i] = new Enemy(game_state, Player);
            }
        }
        void AssignPositions()
        {
            for (int i = 0; i < max_enemies; i++)
            {
                float pos = i * 1900 / max_enemies + 20;
                enemy_container[i]->AssignX(pos);
            }
        }
        void Spawn()
        {
            if(! can_spawn)
            {
                return;
            }
            for (int i = 0; i < max_enemies; i++)
            {
                if(! enemy_container[i]->IsActive())
                {
                    enemy_container[i]->ResetState();
                    break;
                }
            }
        }
        void CountActiveEnemies()
        {
            for (int i = 0; i < max_enemies; i++)
            {
                active_enemies += enemy_container[i]->IsActive();
            }
            
            active_enemies >= max_active_enemies? can_spawn = false: can_spawn = true;
            
        }
    public:
        Spawner(GameState * gs, PlayerObject * player)
        {
            Player = player;
            game_state = gs;
            MakeEnemies();
            AssignPositions();
        }
        virtual void Update()
        {
            for (int i = 0; i < max_enemies; i++)
            {
                enemy_container[i]->Update();
            }
            Spawn();
        }

        virtual void Draw()
        {
            for (int i = 0; i < max_enemies; i++)
            {
                enemy_container[i]->Draw();
            }
        }
};

class Button
{
    private:
        std::string text;
        Rect rectangle;
        bool is_highlighted = false;
        std::function<void()> command;
        GameState * game_state;
        graphics::Brush button_text_brush;
        void ChangeColor(float r, float g, float b)
        {
            Brush.fill_color[0] = r;
            Brush.fill_color[1] = g;
            Brush.fill_color[2] = b;
        }

    public:
        graphics::Brush Brush;
        Button(GameState * gm_state, std::string btn_text, std::function<void()> func){
            game_state = gm_state;
            text = btn_text;
            command = func;

            button_text_brush.fill_color[0] = 0.f;
            button_text_brush.fill_color[1] = 0.f;
            button_text_brush.fill_color[2] = 0.f;
        }
        ~Button()
        {
            std::cout << "Deleting button" << std::endl;
        }
        void EnableDebug()
        {
            rectangle.EnableDebug();
        }

        void CheckIfHighlighted();

        void Draw()
        {
            if(is_highlighted)
            {
                ChangeColor(0.5f,0.3f,0.6f);
            } else{
                ChangeColor(1.f,1.f,1.f);
            }
            rectangle.Draw(Brush);
            //Change the position later
            graphics::drawText(rectangle.GetPosX() - rectangle.GetWidth() / 2, rectangle.GetPosY() + rectangle.GetHeight() / 2, rectangle.GetWidth() / 2, text, button_text_brush);
        }
        void Update();
        //Setters
        void ChangeText(std::string txt)
        {
            text = txt;
        }
        void ChangeCommand(std::function<void()> func)
        {
            command = func;
        }
        void ChangePos(Vector2<float> pos)
        {
            rectangle.ChangePos(pos);
        }
};

#endif // __GAMEOBJECTS_H__
