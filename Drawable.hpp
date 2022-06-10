#pragma once

class Drawable
{
public:
    Drawable()
    {
        y = x = 0;
        icon = ' ';
    }

    Drawable(int _y, int _x, chtype ch)
    {
        y = _y;
        x = _x;
        icon = ch;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    chtype getIcon()
    {
        return icon;
    }

protected:
    int y, x;
    chtype icon;
};