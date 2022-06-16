#pragma once
#include "Drawable.hpp"

#define EMPTYICON ' '

class Empty : public Drawable
{
public:
    Empty(int _y = 0, int _x = 0)
    {
        y = _y;
        x = _x;
        icon = EMPTYICON;
    }
};