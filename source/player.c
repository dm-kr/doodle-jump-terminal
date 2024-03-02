#include "player.h"

#include <stdlib.h>

Player *create_player(Field *field) {
    Player *player = (Player *)malloc(sizeof(Player));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            player->pos[i][j].x = i + field->width / 2 - 1;
            player->pos[i][j].y = j + 2;
            player->image[i][j] = 'X';
        }
    }
    player->direction = 1;
    player->health = 3;
    player->max_health = 3;
    player->score = 0;
    player->max_jump_height = 4;
    player->current_jump_height = 0;
    return player;
}

void reset_player(Field *field, Player *player) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            player->pos[i][j].x = i + field->width / 2 - 1;
            player->pos[i][j].y = j + 2;
        }
    }
}

void move_player(Field *field, Player *player, int x, int y) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            player->pos[i][j].x = (player->pos[i][j].x + field->width + x) % field->width;
            player->pos[i][j].y += y;
        }
    }
}

void update_player(Field *field, Player *player) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            field->cells[player->pos[i][j].x][player->pos[i][j].y] = player->image[i][j];
        }
    }
}