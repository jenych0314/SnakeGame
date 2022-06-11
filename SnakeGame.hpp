#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
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
public:
    // 6/11 생성자 수정
    SnakeGame(int speed = 300)
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
        gameScore.apple_score = 0;
        gameScore.poison_score = 0;
        gameScore.cur_len = 3;
        gameScore.max_len = 3;
        scoreboard.initialize(gameScore);

        game_over = false;
        srand(time(NULL));
        snake.setDirection(down);

        // snake make
        hanleNextPiece(SnakePiece(1, 1));
        hanleNextPiece(snake.nextHead());
        hanleNextPiece(snake.nextHead());

        if (apple == NULL)
            createApple();
        if (poison == NULL)
            createPoison();
    }

    void processInput()
    {
        chtype input = board.getInput();
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
            break;
        default:
            break;
        }
    }

    void updateState() // 수정
    {
        gameOverHandle();
        hanleNextPiece(snake.nextHead());

        if (apple == NULL)
        {
            createApple();
        }
        if (poison == NULL)
        {
            createPoison();
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

private:
    Board board;
    bool game_over;
    Apple *apple;
    Poison *poison;

    Snake snake;
    Scoreboard scoreboard;

    // 6/11
    s_score gameScore;

    void createApple()
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        board.add(*apple);
    }

    void createPoison() // 추가
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        poison = new Poison(y, x);
        board.add(*poison);
    }

    void eatApple()
    {
        delete apple;
        apple = NULL;
        gameScore.apple_score += 1;
        gameScore.cur_len += 1;
        if (gameScore.max_len < gameScore.cur_len)
            gameScore.max_len = gameScore.cur_len;
        scoreboard.updateScore(gameScore);
    }

    void eatPoison() //추가
    {
        delete poison;
        apple = NULL;
        gameScore.poison_score += 1;
        gameScore.cur_len -= 1;
        scoreboard.updateScore(gameScore);
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

                board.add(Empty(emptyRow, emptyCol));
                snake.removePiece();

                emptyRow = snake.tail().getY();
                emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol));
                snake.removePiece();
                break;
            // case 'G':
            //     break;
            case ' ':
            {
                emptyRow = snake.tail().getY();
                emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol));
                snake.removePiece();
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
        if (gameScore.max_len >= 10)
        {
            game_over = true;
        }
        if (gameScore.apple_score >= 10)
        {
            game_over = true;
        }
    }
};