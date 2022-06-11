#pragma once
#include "Drawable.hpp"
#include "stdlib.h"

#define HEIGHT 20
#define WIDTH 50

class Board
{
protected:
    int xMax, yMax;

private:
    WINDOW *board_win;

    void construct(int speed)
    {
        getmaxyx(stdscr, yMax, xMax);

        // 6/11 
        board_win = newwin(HEIGHT, WIDTH, 5, (xMax / 5) - 10);
        wborder(board_win, 'O', 'O', 'O', 'O', '/', '\\', '\\', '/');
        wrefresh(board_win);

        setTimeout(speed);
        keypad(board_win, true);
    }

public:
    // 맵 생성자
    Board()
    {

    }

    Board(int speed)
    {
        construct(speed);
    }

    // 실행
    void initalize()
    {
        clear();
        refresh();
    }

    // Drawable에서 그리기
    void add(Drawable drawable)
    {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch)
    {
        mvwaddch(board_win, y, x, ch);
    }

    chtype getInput()
    {
        return wgetch(board_win);
    }

    void getEmptyCoordinates(int &y, int &x)
    {
        while ((mvwinch(board_win, y = rand() % HEIGHT, x = rand() % WIDTH)) != ' ')
            ;
    }

    chtype getCharAt(int y, int x)
    {
        return mvwinch(board_win, y, x);
    }

    void refresh()
    {
        wrefresh(board_win);
    }

    void setTimeout(int timeout)
    {
        wtimeout(board_win, timeout);
    }

    void removeWindow()
    {
        wclear(board_win);
    }
};