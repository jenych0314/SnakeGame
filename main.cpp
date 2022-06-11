#include <ncurses.h>
#include <iostream>
#include "Board.hpp"
#include "SnakeGame.hpp"

// 6/11 : 맵 배치를 위한 크기조절
// #define BOARD_DIM 17
// #define BOARD_ROWS BOARD_DIM * 1.2
// #define BOARD_COLS BOARD_DIM * 2.5

int main()
{
    initscr();
    refresh();

    noecho();

    curs_set(0);

    // 6/11
    border('*', '*', '*', '*', '*', '*', '*', '*');
    refresh();

    // 6/11
    SnakeGame game = SnakeGame(100);

    while (!game.isOver())
    {
        game.updateState();
        game.processInput();
        game.redraw();
    }

        // WINDOW *gameover = newwin(30, 30, 0, 0);
        // box(gameover, 0 ,0);
        // wprintw(gameover, "GameOver");
        // wrefresh(gameover);

    getch();
    endwin();

    std::cout << "GameOver" << std::endl;

    return 0;
}