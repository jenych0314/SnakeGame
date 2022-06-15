#pragma once

#define TICK 250
#define ITEMTICK 10000

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Board.hpp"
#include "Empty.hpp"
#include "Apple.hpp"
#include "Drawable.hpp"
#include "Snake.hpp"
#include "Scoreboard.hpp"
#include "Poison.hpp"
#include "gameScore.hpp"

class SnakeGame
{
private:
    Board board;
    Apple *apple;
    Poison *poison;
    Snake snake;
    Scoreboard scoreboard;

    bool game_over;
    int tmp_apple_x, tmp_apple_y;
    int tmp_poison_x, tmp_poison_y;
    // 6/15
    int s_time;
    int a_time; // 아이템 리스폰
    int p_time;

    s_score gameScore;

    void createApple()
    {
        int y, x;

        board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        board.add(*apple);

        tmp_apple_x = x;
        tmp_apple_y = y;
        a_time = 0; // 10초
    }

    void createPoison()
    {
        int y, x;

        board.getEmptyCoordinates(y, x);
        poison = new Poison(y, x);
        board.add(*poison);

        tmp_poison_x = x;
        tmp_poison_y = y;
        p_time = 0; // 10초
    }

    void eatApple()
    {
        delete apple;
        apple = NULL;

        gameScore.apple_score += 1;
        gameScore.cur_len += 1;
        if (gameScore.max_len < gameScore.cur_len)
            gameScore.max_len = gameScore.cur_len;

        a_time = 0;
        scoreboard.updateScore(gameScore);
    }

    void eatPoison()
    {
        delete poison;
        poison = NULL;

        gameScore.poison_score += 1;
        gameScore.cur_len -= 1;

        p_time = 0;
        scoreboard.updateScore(gameScore);
    }

    void removeTail()
    {
        int emptyRow = snake.tail().getY();
        int emptyCol = snake.tail().getX();
        board.add(Empty(emptyRow, emptyCol));
        snake.removePiece();
    }

    void hanleNextPiece(SnakePiece next) // 수정
    {
        if ((apple != NULL) || (poison != NULL))
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();

            // game over handler
            switch (board.getCharAt(next.getY(), next.getX()))
            {
            case 'A':
                eatApple();
                break;
            case 'P':
                eatPoison();
                removeTail();
                removeTail();
                break;
            // case 'G': // Gate 진입 진출 함수 실행
            //     break;
            case ' ':
            {
                removeTail();
                break;
            }
            default: // 'W'
                game_over = true;
                break;
            }
        }
        board.add(next);
        snake.addPiece(next);
    }

    void gameOverHandle() // 추가
    {
        if (snake.getWrongDirection())
        {
            game_over = true;
        }
        if (snake.getSize3())
        {
            game_over = true;
        }
        if (gameScore.max_len >= 10 && gameScore.apple_score >= 10 && gameScore.poison_score >= 2)
        {
            game_over = true;
        }
    }

public:
    SnakeGame(int speed)
    {
        board = Board(speed);
        scoreboard = Scoreboard();
        initalize();
        srand(time(NULL));
    }

    ~SnakeGame()
    {
        delete apple;
    }

    void initalize() // 수정
    {
        apple = NULL;
        poison = NULL;
        board.initalize();

        // score;
        gameScore.apple_score = gameScore.poison_score = 0;
        gameScore.cur_len = gameScore.max_len = 3;
        gameScore.game_time = 0;
        scoreboard.initialize(gameScore);

        s_time = 0;
        a_time = 0;
        p_time = 0;
        game_over = false;
        srand(time(NULL));

        // snake make
        snake.setDirection(down);
        hanleNextPiece(SnakePiece(1, 1));
        hanleNextPiece(snake.nextHead());
        hanleNextPiece(snake.nextHead());

        if (apple == NULL)
            createApple();
    }

    void processInput()
    {
        chtype input = board.getInput();

        int old_timeout = board.getTimeout();
        // process input
        switch (input)
        {
        case KEY_UP:
        case 'w':
            snake.setDirection(up);
            break;
        case KEY_DOWN:
        case 's':
            snake.setDirection(down);
            break;
        case KEY_RIGHT:
        case 'd':
            snake.setDirection(right);
            break;
        case KEY_LEFT:
        case 'a':
            snake.setDirection(left);
            break;
        case 'p':
            board.setTimeout(-1);
            while (board.getInput() != 'p')
                ;
            board.setTimeout(old_timeout);
            break;
        default:
            break;
        }
    }

    void updateState() // 수정
    {
        // 6/15
        s_time += TICK;
        a_time += TICK;
        p_time += TICK;

        if (s_time % 1000 == 0)
        {
            gameScore.game_time += 1;
            scoreboard.updateScore(gameScore);
        }

        gameOverHandle();
        hanleNextPiece(snake.nextHead());

        if (apple == NULL)
        {
            createApple();
        }
        if ((gameScore.max_len > 5) && (poison == NULL))
        {
            createPoison();
        }

        if (a_time == ITEMTICK)
        {
            board.addAt(tmp_apple_y, tmp_apple_x, ' ');
            a_time = 0;

            delete apple;
            apple = NULL;
        }
        if (p_time == ITEMTICK)
        {
            board.addAt(tmp_poison_y, tmp_poison_x, ' ');
            p_time = 0;

            delete poison;
            poison = NULL;
        }
        // tmp
        if ((s_time % (ITEMTICK + TICK) == 0) && (gameScore.cur_len <= snake.getCurSize()))
        {
            removeTail();
        }
    }

    void redraw()
    {
        board.refresh();
        scoreboard.refresh();
    }

    bool isOver()
    {
        return game_over;
    }
};