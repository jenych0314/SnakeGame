#pragma once
#include "Drawable.hpp"

#define GATEICON 'O';

class Gate : public Drawable
{
public:
    Gate(int _y = 0, int _x = 0)
    {
        y = _y;
        x = _x;
        icon = GATEICON;
    }
};