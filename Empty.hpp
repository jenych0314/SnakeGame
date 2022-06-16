#pragma once
#include "Drawable.hpp"

const char EMPTYICON = ' ';

class Empty : public Drawable
{
public:
    Empty(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = ::EMPTYICON;
    }
};