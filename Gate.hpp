#pragma once // 추가
#include <ncurses.h>
#include "Drawable.hpp"

class Gate : public Drawable
{
public:
    Gate(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = 'G';
    }
};