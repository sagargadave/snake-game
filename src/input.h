#pragma once
#include <termios.h>
#include <cstdlib>

void enableRawMode();
void disableRawMode();
int  readKey();