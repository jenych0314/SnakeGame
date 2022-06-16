#pragma once // 추가
#include "Drawable.hpp"

#define POISONICON 'P'

class Poison : public Drawable
{
public:
    Poison(int _y = 0, int _x = 0)
    {
        y = _y;
        x = _x;
        icon = POISONICON;
    }
};