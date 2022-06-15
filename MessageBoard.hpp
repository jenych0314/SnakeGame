#pragma once

#include <ncurses.h>

class MessageBoard
{
private:
    WINDOW *explain;

    void construct()
    {
        explain = newwin(10, 50, 30, 60);
        box(explain, 0, 0);
        wrefresh(explain);
    }

public:
    MessageBoard()
    {
        construct();
    }

    void initialize()
    {
        mvwprintw(explain, 1, 3, "Game Rule");
        mvwprintw(explain, 2, 3, "Eat 'A' makes your snake length + 1");
        mvwprintw(explain, 3, 3, "Eat 'P' makes your snake length - 1");
        mvwprintw(explain, 4, 3, "If current length less than 3, Game Over");
        mvwprintw(explain, 5, 3, "If clear all mission, Game Clear");
        refresh();
    }

    void pauseMessage()
    {
        mvwprintw(explain, 6, 3, "Game Pause");
        refresh();
    }

    void refresh()
    {
        wrefresh(explain);
    }
};