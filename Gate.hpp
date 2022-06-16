#pragma once
#include "Drawable.hpp"

const char GATEICON = 'O';

class Gate : public Drawable
{
public:
    Gate(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = ::GATEICON;
    }
};