#ifndef GAMESCORE_HPP
#define GAMESCORE_HPP

typedef struct Score_menu
{
    int cur_len;
    int max_len;
    int apple_score;
    int poison_score;
    int gate_score;
    int game_time;

    int mission_len;
    int mission_apple;
    int mission_poison;
    int mission_gate;
    int mission_time;

    Score_menu()
    {
        cur_len = max_len = 3;
        apple_score = poison_score = gate_score = game_time = 0;
        mission_len = mission_apple = 10;
        mission_poison = mission_gate = 2;
        mission_time = 60;
    }
} s_score;

#endif