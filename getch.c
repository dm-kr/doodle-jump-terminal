#include "getch.h"

#include <stdio.h>

struct termios oldSettings, newSettings;

void initTermios() {
    fcntl(0, F_SETFL, O_NONBLOCK);
    tcgetattr(0, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &newSettings);
}

void resetTermios() { tcsetattr(0, TCSANOW, &oldSettings); }

char getch() {
    char ch;
    initTermios(oldSettings, newSettings);
    ch = getchar();
    resetTermios(oldSettings);
    return ch;
}