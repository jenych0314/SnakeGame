#pragma once
#include <curses.h>
#include <ncurses.h>

#include <iostream>


class Scoreboard : public Board
{
    WINDOW *score_win;

public:
    Scoreboard()
    {
        score_win = newwin(30, 30, 5, (xMax / 2) + 30);
        box(score_win, 0, 0);
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