#pragma once
#include "gameScore.hpp"


class Scoreboard
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

        mvwprintw(score_win, 7, 1, "MISSON");
        mvwprintw(score_win, 8, 1, "Grow your length : %d / 10 ", gameScore.max_len);
        mvwprintw(score_win, 9, 1, "Eat Apple Count : %d / 10 ", gameScore.apple_score);
        mvwprintw(score_win, 10, 1, "Eat Posion Count : %d / 2 ", gameScore.poison_score);
        mvwprintw(score_win, 11, 1, "Game Time : ");
        
        
        // mvwprintw(score_win, 5, 1, "Gate Count : %d ", score);
    }

    void refresh()
    {
        wrefresh(score_win);
    }
};