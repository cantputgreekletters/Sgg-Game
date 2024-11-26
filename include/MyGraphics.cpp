#include "include/MyGraphics.h"

namespace my_graphics {
    int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;
    void DrawVectorLine(Vector2<float> pos_1, Vector2<float> pos_2, graphics::Brush brush)
    {
        graphics::drawLine(pos_1.x, pos_1.y, pos_2.x, pos_2.y, brush);
    }
    void DrawMouseCords(Vector2<int> mouse,graphics::Brush br, Vector2<float> pos)
    {
        std::string text_x = "Mouse pos x : " + std::to_string(mouse.x);
        std::string text_y = "Mouse pos y : " + std::to_string(mouse.y);

        graphics::drawText(pos.x, pos.y,10,text_x, br);
        graphics::drawText(pos.x, pos.y + 20,10,text_y, br);
    }

    void EndGame()
    {
        graphics::stopMessageLoop();
    }
};