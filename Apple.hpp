#pragma once
#include "Drawable.hpp"

extern const char APPLEICON = 'A';

class Apple : public Drawable
{
public:
    Apple(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = ::APPLEICON;
    }
};