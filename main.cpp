#include <ncurses.h>
#include "Board.hpp"
#include "SnakeGame.hpp"
#include <iostream>
#include <chrono>

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
    mvwprintw(explain, 1, 3, "Game Rule\nEat 'A' makes your snake length + 1\n Eat 'P' makes your snake length - 1\n if current length less than 3, Game Over\n if clear all mission, Game Clear");
    wrefresh(explain);

    SnakeGame game = SnakeGame(100);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    int time = 0;

    while (!game.isOver())
    {
        game.updateState();
        game.processInput();
        game.redraw();
        std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
        if (time < sec.count())
            time = sec.count();
        std::cout << time << " / 30" << std::endl;
    }
    

    getch();
    endwin();

    std::cout << "GameOver" << std::endl;
    

    return 0;
}