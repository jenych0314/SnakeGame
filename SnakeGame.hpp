#pragma once

#include <ncurses.h>
// #include <ncursesw/curses.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Drawable.hpp"
#include "Apple.hpp"
#include "Poison.hpp"
#include "Gate.hpp"
#include "Empty.hpp"
#include "Snake.hpp"
#include "Board.hpp"
#include "Scoreboard.hpp"
#include "gameScore.hpp"
#include "MessageBoard.hpp"

const int tick = 250;
const int itemTick = 10000;

extern const char APPLEICON;
extern const char POISONICON;
extern const char GATEICON;
extern const char EMPTYICON;
extern const char SNAKEICON;

class SnakeGame
{
private:
    Apple *apple;
    Poison *poison;
    Gate *gate1, *gate2;
    Snake snake;
    Board board;
    Scoreboard scoreboard;
    MessageBoard messageBoard;

    s_score gameScore;

    bool gamePause, gameOver, gameClear;
    int tmp_apple_x, tmp_apple_y;
    int tmp_poison_x, tmp_poison_y;
    int tmp_gate1_x, tmp_gate1_y, tmp_gate2_x, tmp_gate2_y;
    int snakeTime, appleTime, poisonTime, gateTime; // handle Item respon time

    void createApple()
    {
        int y, x;

        board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        board.add(*apple);

        tmp_apple_x = x;
        tmp_apple_y = y;
        appleTime = 0;
    }

    void createPoison()
    {
        int y, x;

        board.getEmptyCoordinates(y, x);
        poison = new Poison(y, x);
        board.add(*poison);

        tmp_poison_x = x;
        tmp_poison_y = y;
        poisonTime = 0;
    }

    void createGate()
    {
        int y1, x1, y2, x2;

        board.getWallCoordinates(y1, x1, y2, x2);
        gate1 = new Gate(y1, x1);
        gate2 = new Gate(y2, x2);
        board.add(*gate1);
        board.add(*gate2);

        tmp_gate1_x = x1;
        tmp_gate1_y = y1;
        tmp_gate2_x = x2;
        tmp_gate2_y = y2;
        gateTime = 0;
    }

    void eatApple()
    {
        delete apple;
        apple = NULL;

        gameScore.apple_score += 1;
        gameScore.cur_len += 1;
        if (gameScore.max_len < gameScore.cur_len)
            gameScore.max_len = gameScore.cur_len;

        appleTime = 0;
        scoreboard.updateScore(gameScore);
    }

    void eatPoison()
    {
        delete poison;
        poison = NULL;

        gameScore.poison_score += 1;
        gameScore.cur_len -= 1;

        poisonTime = 0;
        scoreboard.updateScore(gameScore);
    }

    void passGate()
    {
        // 꼬리까지 전부 나오면
        // delete gate1, gate2;
        // gate1 = gate2 = NULL;
        // gameScore.gate_score += 1;
        // gateTime = 0;
        // scoreboard.updateScore(gameScore);
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
            char boardCharAt = board.getCharAt(next.getY(), next.getX());
            // game over handler
            switch (boardCharAt)
            {
            case 'A':
                eatApple();
                break;
            case 'P':
                eatPoison();
                removeTail();
                removeTail();
                break;
            case 'O': // Gate 진입 진출 함수 실행
                passGate();
                break;
            case ' ':
            {
                removeTail();
                break;
            }
            default: // 'W'
                gameOver = true;
                break;
            }
        }
        else
        {
            if (appleTime == ::tick)
                removeTail();
        }
        board.add(next);
        snake.addPiece(next);
    }

    void gameOverHandle() // 추가
    {
        if (snake.getWrongDirection())
        {
            gameOver = true;
        }
        if (snake.getSize3())
        {
            gameOver = true;
        }
        if (gameScore.max_len >= gameScore.mission_len && gameScore.apple_score >= gameScore.mission_apple && gameScore.poison_score >= gameScore.mission_poison && gameScore.gate_score >= gameScore.mission_gate && gameScore.game_time >= gameScore.mission_time)
        {
            gameOver = gameClear = true;
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
        gate1 = gate2 = NULL;
        board.initalize();
        scoreboard.initialize(gameScore);
        messageBoard.initialize();

        snakeTime = appleTime = poisonTime = gateTime = 0;
        gamePause = gameOver = gameClear = false;
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
            gamePause = true;
            messageBoard.pauseMessage();
            board.setTimeout(-1);
            while (board.getInput() != 'p')
                ;
            gamePause = false;
            messageBoard.initialize();
            board.setTimeout(old_timeout);
            break;
        default:
            break;
        }
    }

    void updateState() // 수정
    {
        // 6/15
        snakeTime += ::tick;
        appleTime += ::tick;
        poisonTime += ::tick;

        if (snakeTime % 1000 == 0)
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
        if ((gameScore.max_len > 5) && (gate1 == NULL))
        {
            createGate();
        }

        if (appleTime == ::itemTick)
        {
            // board.addAt(tmp_apple_y, tmp_apple_x, ' ');
            board.add(Empty(tmp_apple_y, tmp_apple_x));
            appleTime = 0;

            delete apple;
            apple = NULL;
        }
        if (poisonTime == ::itemTick)
        {
            // board.addAt(tmp_poison_y, tmp_poison_x, ' ');
            board.add(Empty(tmp_poison_y, tmp_poison_x));
            poisonTime = 0;

            delete poison;
            poison = NULL;
        }
        if (gateTime == ::itemTick)
        {
            // board.addAt(tmp_gate1_y, tmp_gate1_x, ' ');
            // board.addAt(tmp_gate2_y, tmp_gate2_x, ' ');
            board.add(Empty(tmp_gate1_y, tmp_gate1_x));
            board.add(Empty(tmp_gate2_y, tmp_gate2_x));
            gateTime = 0;

            delete gate1, gate2;
            gate1 = gate2 = NULL;
        }
    }

    void redraw()
    {
        board.refresh();
        scoreboard.refresh();
        messageBoard.refresh();
    }

    bool isOver()
    {
        return gameOver;
    }

    bool isClear()
    {
        return gameClear;
    }
};