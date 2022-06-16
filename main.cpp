#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>
// #include <ncursesw/curses.h>
// #include <locale.h>
#include "Board.hpp"
#include "SnakeGame.hpp"

int main()
{
    // setlocale(LC_ALL, "ko_KR.utf-8");
    initscr();
    refresh();
    noecho();
    curs_set(0);

    border('*', '*', '*', '*', '*', '*', '*', '*');
    refresh();

    SnakeGame game = SnakeGame(TICK);

    while (!game.isOver())
    {
        game.redraw();
        game.updateState();
        game.redraw();
        game.processInput();
        game.redraw();
    }

    getch();
    endwin();

    if (game.isClear() && game.isOver())
        std::cout << "GameClear" << std::endl;
    else
        std::cout << "GameOver" << std::endl;

    return 0;
}
