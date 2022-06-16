#pragma once

// const char APPLEICON = 'A';
// const char POISONICON = 'P';
// const char EMPTYICON = ' ';
// const char SNAKEICON = '@';
// const char GATEICON = 'O';
// const char WALLICON = 'W';

class Drawable
{
protected:
    int y, x;
    chtype icon;

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
};