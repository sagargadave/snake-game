#include "board.h"
#include <iostream>
#include <algorithm>

void Board::clearScreen() {
    std::cout << "\033[2J\033[1;1H"; 
}

void Board::draw(
    const std::vector<std::pair<int, int>>& snake,
    std::pair<int, int> food,
    int score,
    int highScore
) {
    clearScreen();

    std::cout << "Score: " << score << " | High Score: " << highScore << "\n";

    for(int x = 0; x < BOARD_WIDTH + 2; ++x) {
        std::cout << WALL;
    }
    std::cout << "\n";

    for(int y = 0; y < BOARD_HEIGHT; ++y) {
        std::cout << WALL;
        for(int x = 0; x < BOARD_WIDTH; ++x) {
            std::pair<int, int> pos = {x, y};

            if(pos == snake.front()) {
                std::cout << SNAKE_HEAD;
            } else if(std::find(snake.begin(), snake.end(), pos) != snake.end()) {
                std::cout << SNAKE_BODY;
            } else if(pos == food) {
                std::cout << FOOD;
            } else {
                std::cout << ' ';
            }
        }
        std::cout << WALL;
        std::cout << "\n";
    }

    for(int x = 0; x < BOARD_WIDTH + 2; ++x) {
        std::cout << WALL;
    }
    std::cout << "\n";
    std::cout << "  WASD/Arrows: Move  |  P: Pause  |  Q: Quit\n";
}