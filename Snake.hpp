#pragma once
#include <queue>

enum Direction
{
    up = -1,
    down = 1,
    left = -2,
    right = 2
};

class SnakePiece : public Drawable
{
public:
    SnakePiece()
    {
        this->x = this->y = 0;
        this->icon = '@';
    }

    SnakePiece(int _y, int _x)
    {
        x = _x;
        y = _y;
        icon = '@';
    }
};

class Snake
{
private:
    std::queue<SnakePiece> prev_pieces;
    Direction cur_direction;
    bool wrongDirection = false;
    bool size3 = false;
    int maxSize, curSize;

public:
    Snake()
    {
        cur_direction = down;
        maxSize = curSize = prev_pieces.size();
    }

    void addPiece(SnakePiece piece)
    {
        prev_pieces.push(piece);
        curSize++;
        if (curSize > maxSize)
        {
            maxSize = curSize;
        }
    }

    void removePiece()
    {
        prev_pieces.pop();
        curSize--;
        if (curSize < 2)
        {
            size3 = true;
        }
    }

    SnakePiece tail()
    {
        return prev_pieces.front();
    }

    SnakePiece head()
    {
        return prev_pieces.back();
    }

    Direction getDirection()
    {
        return cur_direction;
    }

    bool getWrongDirection()
    {
        return this->wrongDirection;
    }

    bool getSize3()
    {
        return this->size3;
    }

    int getCurSize()
    {
        return this->curSize;
    }

    void setDirection(Direction d)
    {
        if (cur_direction == d)
        {
            return;
        }
        else if (cur_direction + d != 0)
        {
            cur_direction = d;
        }
        else
        {
            wrongDirection = true;
        }
    }

    SnakePiece nextHead()
    {
        int row = head().getY();
        int col = head().getX();

        switch (cur_direction)
        {
        case down:
            row++;
            break;
        case up:
            row--;
            break;
        case left:
            col--;
            break;
        case right:
            col++;
            break;
        }

        return SnakePiece(row, col);
    }
};