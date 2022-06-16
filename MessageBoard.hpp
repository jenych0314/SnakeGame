#pragma once

#include <ncurses.h>

// extern const char APPLEICON;
// extern const char POISONICON;
// extern const char EMPTYICON;
// extern const char SNAKEICON;
// extern const char GATEICON;
// extern const char WALLICON;

class MessageBoard
{
private:
    WINDOW *explain;

    void construct()
    {
        explain = newwin(10, 70, 30, 60);
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
        mvwprintw(explain, 4, 3, "If you pass 'O', you will find the other 'O' position.");
        mvwprintw(explain, 5, 3, "If current length less than 3, Game Over");
        mvwprintw(explain, 6, 3, "If clear all mission, Game Clear");
        refresh();
    }

    void pauseMessage()
    {
        mvwprintw(explain, 6, 3, "Game Pause");
        refresh();
    }

    void gameOverMessage()
    {
        mvwprintw(explain, 7, 3, "Game Over");
        refresh();
    }

    void gameClearMessage()
    {
        mvwprintw(explain, 8, 3, "Game Clear");
        refresh();
    }

    void refresh()
    {
        wrefresh(explain);
    }
};