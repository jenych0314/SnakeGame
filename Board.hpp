#pragma once
#include <stdlib.h>
#include <typeinfo>
#include "Drawable.hpp"
#include "Wall.hpp"
#include "Time.hpp"

#define HEIGHT 25
#define WIDTH 60

class Board
{
private:
    WINDOW *board_win;
    int timeout;

    void construct(int tick)
    {
        getmaxyx(stdscr, yMax, xMax);
        // std::cout << xMax << ", " << yMax << std::endl;
        // board_win = newwin(HEIGHT, WIDTH, 5, (xMax / 5) - 10);
        board_win = newwin(HEIGHT, WIDTH, 5, 30);
        // wborder(board_win, '|', '|', '-', '-', '+', '+', '+', '+');
        box(board_win, 0, 0);
        wrefresh(board_win);
        timeout = tick;
        setTimeout(tick);
        keypad(board_win, true);
    }

protected:
    int xMax, yMax;

public:
    // 맵 생성자
    Board()
    {
    }

    Board(int tick)
    {
        construct(tick);
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
        time_t time_last_input = Time::milliseceonds();

        chtype input = wgetch(board_win);
        chtype new_input = ERR;

        setTimeout(0);
        while (time_last_input + timeout >= Time::milliseceonds())
        {
            new_input = wgetch(board_win);
        }
        setTimeout(timeout);

        if (new_input != ERR)
            input = new_input;

        return input;
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

    int getTimeout()
    {
        return timeout;
    }

    void removeWindow()
    {
        wclear(board_win);
    }
};