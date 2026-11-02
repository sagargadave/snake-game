#pragma once
#include <vector>
#include <utility>
#include "config.h"

class Board {
public:
    void draw(
        const std::vector<std::pair<int,int>>& snake,
        std::pair<int,int> food,
        int score,
        int highScore
    );
    void clearScreen();
};