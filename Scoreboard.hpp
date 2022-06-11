#pragma once
#include <ncurses.h>
#include "gameScore.hpp"



class Scoreboard : public Board
{
    WINDOW *score_win;

    void construct()
    {
        // 6/11 
        score_win = newwin(20, 40, 5, 100);
        box(score_win, 0, 0);
        wrefresh(score_win);
    }

public:
    Scoreboard()
    {
        construct();
    }

    void initialize(s_score initial_score) // 수정
    {
        updateScore(initial_score);
        refresh();
    }

    void updateScore(s_score gameScore) // 수정
    {
        mvwprintw(score_win, 1, 1, "Score Board");
        mvwprintw(score_win, 2, 1, "Current Length/Max Length : %d / %d", gameScore.cur_len, gameScore.max_len);
        mvwprintw(score_win, 3, 1, "Eat Apple Count : %d ", gameScore.apple_score);
        mvwprintw(score_win, 4, 1, "Eat Poison Count : %d ", gameScore.poison_score);
        // mvwprintw(score_win, 5, 1, "Gate Count : %d ", score);
    }

    // 아래 게임 설명 만들예정
// %-11llu
    void refresh()
    {
        wrefresh(score_win);
    }

    void removeWindow()
    {
        wclear(score_win);
    }
};