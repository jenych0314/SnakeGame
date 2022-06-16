#pragma once
#include "gameScore.hpp"

class Scoreboard
{
private:
    WINDOW *score_win;

    void construct()
    {
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
        mvwprintw(score_win, 1, 1, "MISSON");
        mvwprintw(score_win, 2, 1, "Grow your length : %d / %d", gameScore.max_len, gameScore.mission_len);
        mvwprintw(score_win, 3, 1, "Eat Apple Count : %d / %d", gameScore.apple_score, gameScore.mission_apple);
        mvwprintw(score_win, 4, 1, "Eat Posion Count : %d / %d", gameScore.poison_score, gameScore.mission_poison);
        mvwprintw(score_win, 5, 1, "Pass Gate Count : %d / %d", gameScore.gate_score, gameScore.mission_gate);
        mvwprintw(score_win, 6, 1, "Game Time : %d / %d", gameScore.game_time, gameScore.mission_time);

        mvwprintw(score_win, 8, 1, "Score Board");
        mvwprintw(score_win, 9, 1, "Current Length/Max Length : %d / %d", gameScore.cur_len, gameScore.max_len);
        mvwprintw(score_win, 10, 1, "Eat Apple Count : %d ", gameScore.apple_score);
        mvwprintw(score_win, 11, 1, "Eat Poison Count : %d ", gameScore.poison_score);
        mvwprintw(score_win, 12, 1, "Gate Count : %d ", gameScore.gate_score);
        mvwprintw(score_win, 13, 1, "Game Time : %d", gameScore.game_time);
    }

    void refresh()
    {
        wrefresh(score_win);
    }
};