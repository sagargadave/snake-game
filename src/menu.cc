#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include "menu.h"
#include "config.h"

void Menu::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

MenuChoice Menu::showMain() {
    while (true) {
        clearScreen();
        std::cout << "\n\n";
        std::cout << "  +---------------------------+\n";
        std::cout << "  |       SNAKE GAME          |\n";
        std::cout << "  +---------------------------+\n";
        std::cout << "  |                           |\n";
        std::cout << "  |     [1] Play              |\n";
        std::cout << "  |     [2] High Score        |\n";
        std::cout << "  |     [3] Quit              |\n";
        std::cout << "  |                           |\n";
        std::cout << "  +---------------------------+\n";
        std::cout << "\n  Choose: ";
        std::cout.flush();

        char ch;
        std::cin >> ch;
        std::cin.ignore(1000, '\n');

        if (ch == '1') return MenuChoice::PLAY;
        if (ch == '2') return MenuChoice::HIGH_SCORE;
        if (ch == '3') return MenuChoice::QUIT;
    }
}

Difficulty Menu::showDifficulty() {
    while (true) {
        clearScreen();
        std::cout << "\n\n";
        std::cout << "  +---------------------------+\n";
        std::cout << "  |    SELECT DIFFICULTY      |\n";
        std::cout << "  +---------------------------+\n";
        std::cout << "  |                           |\n";
        std::cout << "  |     [1] Easy              |\n";
        std::cout << "  |     [2] Medium            |\n";
        std::cout << "  |     [3] Hard              |\n";
        std::cout << "  |                           |\n";
        std::cout << "  +---------------------------+\n";
        std::cout << "\n  Choose: ";
        std::cout.flush();

        char ch;
        std::cin >> ch;
        std::cin.ignore(1000, '\n');

        if (ch == '1') return Difficulty::EASY;
        if (ch == '2') return Difficulty::MEDIUM;
        if (ch == '3') return Difficulty::HARD;
    }
}

void Menu::showGameOver(int score, int highScore) {
    clearScreen();
    std::cout << "\n\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  |        GAME OVER          |\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  |                           |\n";

    std::string scoreLine = "  |   Score:      " + std::to_string(score);
    int sp = 30 - (int)scoreLine.length();
    std::cout << scoreLine;
    for (int i = 0; i < sp; i++) std::cout << " ";
    std::cout << "|\n";

    std::string hsLine = "  |   High Score: " + std::to_string(highScore);
    int hp = 30 - (int)hsLine.length();
    std::cout << hsLine;
    for (int i = 0; i < hp; i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "  |                           |\n";
    std::cout << "  |   [R] Restart             |\n";
    std::cout << "  |   [Q] Quit                |\n";
    std::cout << "  |                           |\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "\n  Choose: ";
    std::cout.flush();
}

void Menu::showHighScore(int highScore) {
    clearScreen();
    std::cout << "\n\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  |       HIGH SCORE          |\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  |                           |\n";

    std::string fullLine = "  |   Best Score: " + std::to_string(highScore);
    int padding          = 30 - (int)fullLine.length();
    std::cout << fullLine;
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "  |                           |\n";
    std::cout << "  |   Press any key to go back|\n";
    std::cout << "  |                           |\n";
    std::cout << "  +---------------------------+\n";
    std::cout.flush();

    termios orig, raw;
    tcgetattr(STDIN_FILENO, &orig);
    raw = orig;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}

void Menu::showPaused() {
    clearScreen();
    std::cout << "\n\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  |         PAUSED            |\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "  |                           |\n";
    std::cout << "  |   P  → Resume             |\n";
    std::cout << "  |   Q  → Quit to Menu       |\n";
    std::cout << "  |                           |\n";
    std::cout << "  +---------------------------+\n";
    std::cout << "\n  Choose: ";
    std::cout.flush();
}

int Menu::loadHighScore() {
    std::ifstream file(HIGH_SCORE_FILE);
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
    }
    return score;
}

void Menu::saveHighScore(int score) {
    std::ofstream file(HIGH_SCORE_FILE);
    if (file.is_open()) {
        file << score;
        file.close();
    }
}