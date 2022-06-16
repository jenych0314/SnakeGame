#pragma once
#include "Drawable.hpp"

#define WALLICON 'Q'

class ImmuneWall : public Drawable
{
public:
    ImmuneWall(int _y = 0, int _x = 0)
    {
        y = _y;
        x = _x;
        icon = WALLICON;
    }
};