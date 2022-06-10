#pragma once // 추가
#include <ncurses.h>
#include "Drawable.hpp"

class Wall : public Drawable
{
public:
    Wall(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = 'W';
    }
};