#pragma once
#include "Drawable.hpp"

#define WALLICON 'X'

class Wall : public Drawable
{
public:
    Wall(int _y = 0, int _x = 0)
    {
        y = _y;
        x = _x;
        icon = WALLICON;
    }
};