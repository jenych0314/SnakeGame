#include <ncurses.h>
#include "Board.hpp"
#include "SnakeGame.hpp"
#include <iostream>
#include <chrono>

#define extern TICK;

int main()
{
    initscr();
    refresh();
    noecho();
    curs_set(0);

    border('*', '*', '*', '*', '*', '*', '*', '*');
    refresh();

    WINDOW *explain = newwin(15, 70, 30, 50);
    box(explain, 0, 0);
    std::string gameMessage = "Game Rule\n"
                              "Eat 'A' makes your snake length + 1\n"
                              "Eat 'P' makes your snake length - 1\n"
                              "if current length less than 3, Game Over\n"
                              "if clear all mission, Game Clear";
    mvwprintw(explain, 1, 3, gameMessage.c_str());
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