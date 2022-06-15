#include <ncurses.h>
#include "Board.hpp"
#include "SnakeGame.hpp"
#include <iostream>
#include <chrono>
#include <vector>

#define extern TICK;

int main()
{
    initscr();
    refresh();
    noecho();
    curs_set(0);

    border('*', '*', '*', '*', '*', '*', '*', '*');
    refresh();

    WINDOW *explain = newwin(10, 50, 30, 60);
    box(explain, 0, 0);
    mvwprintw(explain, 1, 3, "Game Rule");
    mvwprintw(explain, 2, 3, "Eat 'A' makes your snake length + 1");
    mvwprintw(explain, 3, 3, "Eat 'P' makes your snake length - 1");
    mvwprintw(explain, 4, 3, "if current length less than 3, Game Over");
    mvwprintw(explain, 5, 3, "if clear all mission, Game Clear");
    wrefresh(explain);

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