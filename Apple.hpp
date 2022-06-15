#pragma once
#include "Drawable.hpp"

class Apple : public Drawable
{
public:
    Apple(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = 'A';
    }

    char getIcon()
    {
        return this->icon;
    }
};