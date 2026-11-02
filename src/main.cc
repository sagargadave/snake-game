#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "board.h"
#include "snake.h"
#include "config.h"
#include "menu.h"
#include "input.h"

enum class GameState { MENU, PLAYING, PAUSED, GAME_OVER };

std::pair<int,int> generateFood(const std::vector<std::pair<int,int>>& snake) {
    std::pair<int,int> food;
    bool onSnake = true;
    while (onSnake) {
        food = { rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT };
        onSnake = false;
        for (const auto& seg : snake) {
            if (seg == food) { onSnake = true; break; }
        }
    }
    return food;
}

int getSpeed(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::EASY:   return SPEED_EASY;
        case Difficulty::MEDIUM: return SPEED_MEDIUM;
        case Difficulty::HARD:   return SPEED_HARD;
    }
    return SPEED_MEDIUM;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    enableRawMode();

    Menu  menu;
    Board board;
    GameState state = GameState::MENU;

    int score     = 0;
    int highScore = menu.loadHighScore();
    int speed     = SPEED_MEDIUM;

    Snake* snake = nullptr;
    std::pair<int,int> food = {0, 0};

    bool running = true;
    while (running) {

        if (state == GameState::MENU) {
            disableRawMode();
            MenuChoice choice = menu.showMain();

            if (choice == MenuChoice::QUIT) {
                running = false;
            } else if (choice == MenuChoice::HIGH_SCORE) {
                menu.showHighScore(highScore);
            } else if (choice == MenuChoice::PLAY) {
                Difficulty diff = menu.showDifficulty();
                speed = getSpeed(diff);
                delete snake;
                snake = new Snake();
                food  = generateFood(snake->getBody());
                score = 0;
                enableRawMode();
                state = GameState::PLAYING;
            }

        } else if (state == GameState::PLAYING) {
            int key = readKey();
            if (key == 'w') snake->setDirection(Direction::UP);
            if (key == 's') snake->setDirection(Direction::DOWN);
            if (key == 'a') snake->setDirection(Direction::LEFT);
            if (key == 'd') snake->setDirection(Direction::RIGHT);
            if (key == 'q') { state = GameState::GAME_OVER; continue; }
            if (key == 'p' || key == 'P') { state = GameState::PAUSED; continue; }

            bool ate = (snake->getHeadPosition() == food);
            if (ate) {
                score += 10;
                food = generateFood(snake->getBody());
            }

            snake->move(ate);

            if (snake->checkWallCollision() || snake->checkSelfCollision()) {
                if (score > highScore) {
                    highScore = score;
                    menu.saveHighScore(highScore);
                }
                state = GameState::GAME_OVER;
                continue;
            }

            board.draw(snake->getBody(), food, score, highScore);
            Direction dir = snake->getDirection();
            bool isVertical = (dir == Direction::UP || dir == Direction::DOWN);
            usleep(isVertical ? speed * 1800 : speed * 1000);

        } else if (state == GameState::PAUSED) {
            disableRawMode();
            menu.showPaused();

            char ch = 0;
            std::cin >> ch;
            std::cin.ignore(1000, '\n');

            if (ch == 'p' || ch == 'P') {
                enableRawMode();
                state = GameState::PLAYING;
            } else if (ch == 'q' || ch == 'Q') {
                state = GameState::MENU;
            }

        } else if (state == GameState::GAME_OVER) {
            disableRawMode();
            menu.showGameOver(score, highScore);

            char ch = 0;
            std::cin >> ch;
            std::cin.ignore(1000, '\n');

            if (ch == 'r' || ch == 'R') {
                Difficulty diff = menu.showDifficulty();
                speed = getSpeed(diff);
                delete snake;
                snake = new Snake();
                food  = generateFood(snake->getBody());
                score = 0;
                enableRawMode();
                state = GameState::PLAYING;
            } else if (ch == 'q' || ch == 'Q') {
                running = false;
            }
        }
    }

    delete snake;
    return 0;
}