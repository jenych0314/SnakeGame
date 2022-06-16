#pragma once // 추가
#include "Drawable.hpp"

const char POISONICON = 'P';

class Poison : public Drawable
{
public:
    Poison(int _y, int _x)
    {
        y = _y;
        x = _x;
        icon = ::POISONICON;
    }
};