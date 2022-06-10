#include <ncurses.h>
#include <iostream>
#include "Board.hpp"
#include "SnakeGame.hpp"

#define BOARD_DIM 17
#define BOARD_ROWS BOARD_DIM * 1.2
#define BOARD_COLS BOARD_DIM * 2.5

int main()
{
    initscr();
    refresh();

    noecho();

    curs_set(0);

    SnakeGame game = SnakeGame(BOARD_ROWS, BOARD_COLS, 100);

    while (!game.isOver())
    {
        game.processInput();
        // get input from user

        game.updateState();

        // redraw display
        game.redraw();
    }

    getch();
    endwin();

    std::cout << "GameOver" << std::endl;

    return 0;
}