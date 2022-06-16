#pragma once
#include "Drawable.hpp"

#define APPLEICON 'A'

class Apple : public Drawable
{
public:
    Apple(int _y = 0, int _x = 0)
    {
        y = _y;
        x = _x;
        icon = APPLEICON;
    }
};