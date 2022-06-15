#ifndef GAMESCORE_HPP
#define GAMESCORE_HPP

typedef struct Score_menu
{
    int cur_len;
    int max_len;
    int apple_score;
    int poison_score;
    int game_time;

    Score_menu()
    {
        cur_len = max_len = 3;
        apple_score = poison_score = game_time = 0;
    }
} s_score;

#endif