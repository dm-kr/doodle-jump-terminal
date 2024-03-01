#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "field.h"

typedef struct Pos {
    int x;
    int y;
} Pos;

typedef struct Player {
    Pos pos[2][2];
    int direction;
    int health;
    int max_health;
    int score;
    char image[2][2];
} Player;

Player *create_player(Field *field);
void reset_player(Field *field, Player *player);
void move_player(Field *field, Player *player, int x, int y);
void update_player(Field Field, Player player);

#endif