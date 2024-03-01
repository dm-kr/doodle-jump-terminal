#ifndef _GETCH_H_
#define _GETCH_H_

#include <fcntl.h>
#include <termios.h>

void initTermios();
void resetTermios();
char getch();

#endif