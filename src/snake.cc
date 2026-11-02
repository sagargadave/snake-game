#include "snake.h"
#include <algorithm>

Snake::Snake() {
    int cx = BOARD_WIDTH / 2;
    int cy = BOARD_HEIGHT / 2;
    body = {
        {cx, cy},
        {cx - 1, cy},
        {cx - 2, cy}
    };
    dir = Direction::RIGHT;
    pendingDir = dir;
}

bool Snake::setDirection(Direction newDir) {
    if (newDir == Direction::UP && pendingDir == Direction::DOWN) return false;
    if (newDir == Direction::DOWN && pendingDir == Direction::UP) return false;
    if (newDir == Direction::LEFT && pendingDir == Direction::RIGHT) return false;
    if (newDir == Direction::RIGHT && pendingDir == Direction::LEFT) return false;
    pendingDir = newDir;
    return true;
}

void Snake::move(bool ate) {
    dir = pendingDir;
    auto head = body.front();

    switch (dir) {
        case Direction::UP:    head.second--; break;
        case Direction::DOWN:  head.second++; break;
        case Direction::LEFT:  head.first--; break;
        case Direction::RIGHT: head.first++; break;
    }

    body.insert(body.begin(), head);
    if (!ate) {
        body.pop_back();   
    }
}

bool Snake::checkWallCollision() const {
    auto head = body.front();
    return head.first < 0 || head.first >= BOARD_WIDTH ||
           head.second < 0 || head.second >= BOARD_HEIGHT;
}

bool Snake::checkSelfCollision() const {
    auto head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == head) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> Snake::getHeadPosition() const {
    return body.front();
}

const std::vector<std::pair<int, int>>& Snake::getBody() const {
    return body;
}

Direction Snake::getDirection() const {
    return dir;
}