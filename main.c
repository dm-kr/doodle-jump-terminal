#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "bars.h"
#include "field.h"
#include "getch.h"
#include "player.h"
#include "render.h"

void mainloop(Field *field, Player *player, Bars *bars, int fps);
void handle_controls(Field *field, Player *player, char key);
void handle_ceiling_collision(Player *player, Field *field);
void game_step(Field *field, Player *player, Bars *bars);
void print_results(Player player);

int main() {
    Bars *bars = create_bars(20);
    Field *field = create_field(35, 24);
    Player *player = create_player(field);

    mainloop(field, player, bars, 90);
    print_results(*player);
    destroy_field(field);
    destroy_bars(bars);
    free(player);
    return 0;
}

void mainloop(Field *field, Player *player, Bars *bars, int fps) {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000000 / fps;
    int error_flag = 0;
    int vertical_frequency = 18;
    int tick = 0;
    char key;
    while ((key = getch()) != 'q' && player->health > 0 && error_flag == 0) {
        clear_field(field);
        update_bars(field, bars);
        render(*field, *player);
        handle_controls(field, player, key);
        if (tick == vertical_frequency) {
            game_step(field, player, bars);
            tick = 0;
        }
        handle_ceiling_collision(player, field);
        nanosleep(&ts, NULL);
        error_flag = system("clear");
        tick++;
    }
}

void handle_controls(Field *field, Player *player, char key) {
    if (key == 'a') {
        move_player(field, player, -1, 0);
    }
    if (key == 'd') {
        move_player(field, player, 1, 0);
    }
}

void handle_ceiling_collision(Player *player, Field *field) {
    if (player->direction == -1 && player->pos[0][0].y < 0) {
        reset_player(field, player);
        player->health--;
        player->direction = 1;
        player->current_jump_height = 0;
    }
}

void game_step(Field *field, Player *player, Bars *bars) {
    if (player->pos[0][1].y < field->height - 1 || player->direction == -1) {
        move_player(field, player, 0, player->direction);
    }
    player->current_jump_height++;
    if (player->current_jump_height == player->max_jump_height) {
        player->direction = -1;
        player->current_jump_height = 0;
    }
    if (check_bars_collision(*player, bars) == 1) {
        player->score++;
        player->direction = 1;
        player->current_jump_height = 0;
    }
    if (player->direction == 1) {
        move_bars(field, bars);
    }
}

void print_results(Player player) {
    printf("-------------------------------\n");
    printf("      Your score is %04d!\n", player.score);
    printf("-------------------------------\n");
}