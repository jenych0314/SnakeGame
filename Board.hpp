#pragma once
#include "Drawable.hpp"
#include <stdlib.h>
#include "Time.hpp"

#define HEIGHT 25
#define WIDTH 60

class Board
{

private:
    WINDOW *board_win;

    // 6/15
    int timeout;

    void construct(int tick)
    {
        // 6/11
        board_win = newwin(HEIGHT, WIDTH, 5, 30);
        wborder(board_win, 'O', 'O', 'O', 'O', '/', '\\', '\\', '/');
        wrefresh(board_win);

        timeout = tick;
        setTimeout(tick);
        keypad(board_win, true);
    }

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

    // 6/15
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