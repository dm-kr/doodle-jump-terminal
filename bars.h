#ifndef _BARS_H_
#define _BARS_H_

#include "field.h"
#include "player.h"

typedef struct Bars {
    Pos *bars;
} Bars;

Bars *create_bars(int bars_amount);
void update_bars(Field *field, Bars *bars);
void move_bars(Field *field, Bars *bars);
int check_bars_collision(Player player, Bars *bars);
void destroy_bars(Bars *bars);

#endif