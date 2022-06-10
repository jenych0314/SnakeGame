#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Empty : public Drawable
{
public:
    Empty(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = ' ';
    }
};