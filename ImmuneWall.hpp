#pragma once // 추가
#include <ncurses.h>
#include "Drawable.hpp"

class ImmuneWall : public Drawable
{
public:
    ImmuneWall(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = 'W';
    }
};