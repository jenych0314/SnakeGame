#pragma once

#include <ncurses.h>
// #include <ncursesw/curses.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <typeinfo>
#include "Drawable.hpp"
#include "Empty.hpp"
#include "Apple.hpp"
#include "Poison.hpp"
#include "Gate.hpp"
#include "Wall.hpp"
#include "Snake.hpp"
#include "Board.hpp"
#include "Scoreboard.hpp"
#include "gameScore.hpp"
#include "MessageBoard.hpp"

#define TICK 250
#define ITEMTICK 10000

class SnakeGame
{
private:
    Apple *apple;
    Poison *poison;
    Gate *gate1, *gate2;
    Wall ***walls;
    bool **isWalls;
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

    void createWall()
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            if (i % (HEIGHT - 1))
            {
                for (int j = 0; j < WIDTH; j++)
                {
                    if (j % (WIDTH - 1))
                    {
                        isWalls[i][j] = false;
                        walls[i][j] = NULL;
                    }
                    else
                    {
                        isWalls[i][j] = true;
                        walls[i][j] = new Wall(i, j);
                        board.add(Wall(i, j));
                    }
                }
            }
            else
            {
                for (int j = 0; j < WIDTH; j++)
                {
                    isWalls[i][j] = true;
                    walls[i][j] = new Wall(i, j);
                    board.add(Wall(i, j));
                }
            }
        }
    }

    void createGate()
    {
        int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
        while (y1 == y2 && x1 == x2)
        {
            while (true)
            {
                y1 = rand() % HEIGHT;
                x1 = rand() % WIDTH;
                if (isWalls[y1][x1])
                {
                    break;
                }
            }
            while (true)
            {
                y2 = rand() % HEIGHT;
                x2 = rand() % WIDTH;
                if (isWalls[y2][x2])
                {
                    break;
                }
            }
        }

        delete walls[y1][x1], walls[y2][x2];
        walls[y1][x1] = walls[y2][x2] = NULL;
        isWalls[y1][x1] = isWalls[y2][x2] = false;

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
        // 어떤 게이트와 접촉했는가?

        // if (꼬리까지 전부 나오면)
        // {
        //     delete gate1, gate2;
        //     gate1 = gate2 = NULL;

        //     gateTime = 0;
        //     gameScore.gate_score += 1;
        //     scoreboard.updateScore(gameScore);
        // }
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
        if ((apple != NULL) || (poison != NULL) || (gate1 != NULL))
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
            if (appleTime == (ITEMTICK + TICK))
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
        walls = new Wall **[HEIGHT];
        for (int i = 0; i < HEIGHT; i++)
        {
            walls[i] = new Wall *[WIDTH];
        }
        isWalls = new bool *[HEIGHT];
        for (int i = 0; i < HEIGHT; i++)
        {
            isWalls[i] = new bool[WIDTH];
        }

        board.initalize();
        scoreboard.initialize(gameScore);
        messageBoard.initialize();

        snakeTime = 0;
        gamePause = gameOver = gameClear = false;
        srand(time(NULL));

        // snake make
        snake.setDirection(down);
        hanleNextPiece(SnakePiece(HEIGHT / 2, WIDTH / 2));
        hanleNextPiece(snake.nextHead());
        hanleNextPiece(snake.nextHead());

        if (apple == NULL)
            createApple();
        createWall();
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
        snakeTime += TICK;
        appleTime += TICK;
        poisonTime += TICK;
        gateTime += TICK;

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

        if (appleTime == ITEMTICK)
        {
            board.add(Empty(tmp_apple_y, tmp_apple_x));

            delete apple;
            apple = NULL;
        }
        if (poisonTime == ITEMTICK)
        {
            board.add(Empty(tmp_poison_y, tmp_poison_x));

            delete poison;
            poison = NULL;
        }
        if (gateTime == ITEMTICK)
        {
            board.add(Wall(tmp_gate1_y, tmp_gate1_x));
            board.add(Wall(tmp_gate2_y, tmp_gate2_x));

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