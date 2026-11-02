#include <unistd.h>
#include <cstdio>
#include "input.h"

static termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);  
    atexit(disableRawMode);                  

    termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int readKey() {
    char c = 0;
    read(STDIN_FILENO, &c, 1);
    if (c == 27) {
        char seq[2];
        read(STDIN_FILENO, &seq[0], 1);
        read(STDIN_FILENO, &seq[1], 1);
        if (seq[0] == 91) {
            if (seq[1] == 65) return 'w';
            if (seq[1] == 66) return 's';
            if (seq[1] == 67) return 'd';
            if (seq[1] == 68) return 'a';
        }
    }
    return c;
}