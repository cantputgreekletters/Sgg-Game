#if !defined(__MYGRAPHICS_H__)
#define __MYGRAPHICS_H__

#include "include/MyMath.h"
#include "sgg/graphics.h"
#include <string>
namespace my_graphics {
    void DrawVectorLine(Vector2<float> pos_1, Vector2<float> pos_2, graphics::Brush brush);
    void DrawMouseCords(Vector2<int> mouse,graphics::Brush br, Vector2<float> pos);
    void EndGame();
}

#endif // __MYGRAPHICS_H__