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
private:
    Board board;
    bool game_over;
    Apple *apple;
    Poison *poison;
    double appleTime, poisonTime, gateTime;
    Snake snake;
    Scoreboard scoreboard;
    int tmp_apple_x, tmp_apple_y;
    int tmp_poison_x, tmp_poison_y;

    // 6/11
    s_score gameScore;

    void createApple()
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        tmp_apple_x = x;
        tmp_apple_y = y;
        board.add(*apple);
        appleTime = clock();
    }

    void createPoison() // 추가
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        poison = new Poison(y, x);
        tmp_poison_x = x;
        tmp_poison_y = y;
        board.add(*poison);
        poisonTime = clock();
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
        poison = NULL;
        gameScore.poison_score += 1;
        gameScore.cur_len -= 1;
        scoreboard.updateScore(gameScore);
    }

    void removeTail() // handleNextPiece 내부 동작을 밖으로 빼서 가독성 높여봄.
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
        gameScore.apple_score = gameScore.poison_score = 0;
        gameScore.cur_len = gameScore.max_len = 3;
        scoreboard.initialize(gameScore);
        game_over = false;
        srand(time(NULL));

        // snake make
        snake.setDirection(down);
        hanleNextPiece(SnakePiece(1, 1));
        hanleNextPiece(snake.nextHead());
        hanleNextPiece(snake.nextHead());

        if (apple == NULL)
            createApple();
        // if (poison == NULL) // poison은 snake's max length가 5 이후부터 생성
        //     createPoison();
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
        if ((gameScore.max_len > 5) && (poison == NULL))
        {
            createPoison();
        }

        if ((clock() - appleTime)  > 5000)
        {
            board.addAt(tmp_apple_y, tmp_apple_x, ' ');
            delete apple;
            apple = NULL;
        }
        if ((clock() - poisonTime) > 5000)
        {
            board.addAt(tmp_poison_y, tmp_poison_x, ' ');
            delete poison;
            poison = NULL;
        }
        // if ((clock() - gate->getTime()) / 1000 > 5)
        // {
        //     gate = NULL;
        // }
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