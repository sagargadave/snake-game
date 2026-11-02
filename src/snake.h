#pragma once 
#include <vector>
#include <utility> 
#include "config.h"

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
    public:
        Snake();

        void move(bool ate);
        bool setDirection(Direction newDir);
        bool checkWallCollision() const;
        bool checkSelfCollision() const;

        std::pair<int, int> getHeadPosition() const;
        const std::vector<std::pair<int, int>>& getBody() const;
        Direction getDirection() const;
 
    private:
        std::vector<std::pair<int,int>> body;
        Direction dir;
        Direction pendingDir;
};