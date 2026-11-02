#pragma once
#include <string>

enum class MenuChoice { PLAY, HIGH_SCORE, QUIT };
enum class Difficulty { EASY, MEDIUM, HARD };

class Menu {
public:
    MenuChoice showMain();
    Difficulty showDifficulty();
    void showGameOver(int score, int highScore);
    void showHighScore(int highScore);
    void showPaused();

    int  loadHighScore();
    void saveHighScore(int score);

private:
    void clearScreen();
    const std::string HIGH_SCORE_FILE = "highscore.txt";
};