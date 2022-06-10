#pragma once
#include <curses.h>
#include <ncurses.h>

class Scoreboard
{
    WINDOW *score_win;

public:
    Scoreboard()
    {
    }

    Scoreboard(int width, int y, int x)
    {
        score_win = newwin(1, width, y, x);
    }

    void initialize(int initial_score) // 수정
    {
        clear();
        updateScore(initial_score);
        refresh();
    }

    void updateScore(int score) // 수정
    {
        mvwprintw(score_win, 0, 0, "Score: %-11llu", score);
    }

    void clear()
    {
        wclear(score_win);
    }

    void refresh()
    {
        wrefresh(score_win);
    }
};