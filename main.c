#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "field.h"
#include "getch.h"
#include "player.h"

int check_collision(Player player, Pos *bars);
void update_bars(Field *field, Pos *bars);
void render(Field field, Player player);

int main() {
    Pos *bars = (Pos *)malloc(sizeof(Pos) * 20);
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        bars[i].x = (rand() / 2) % 26 + 1;
        bars[i].y = 3 * i + 2;
    }
    printf("\n");
    int fps = 90;
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000000 / fps;
    Field *field = create_field(35, 24);
    Player *player = create_player(field);
    char key;
    int interval = 18;
    int iter = 0;
    int jump_height = 4;
    int jump_iter = 0;
    while ((key = getch()) != 'q' && player->health > 0) {
        if (system("clear") == -1) return -1;
        clear_field(field);
        update_bars(field, bars);
        render(*field, *player);
        if (key == 'a') {
            move_player(field, player, -1, 0);
        }
        if (key == 'd') {
            move_player(field, player, 1, 0);
        }
        if (iter == interval) {
            if (player->pos[0][1].y < field->height - 1 || player->direction == -1) {
                move_player(field, player, 0, player->direction);
            }
            jump_iter++;
            if (jump_iter == jump_height) {
                player->direction = -1;
                jump_iter = 0;
            }
            if (check_collision(*player, bars) == 1) {
                player->score++;
                player->direction = 1;
                jump_iter = 0;
            }
            if (player->direction == 1) {
                for (int i = 0; i < 20; i++) {
                    bars[i].y--;
                    if (bars[i].y < 0) {
                        bars[i].y += 60;
                        bars[i].x = (rand() / 2) % 26 + 1;
                    }
                }
            }
            iter = 0;
        }
        if (player->direction == -1 && player->pos[0][0].y < 0) {
            player->health--;
            reset_player(field, player);
            player->direction = 1;
            jump_iter = 0;
        }
        iter++;
        nanosleep(&ts, NULL);
    }
    if (system("clear") == -1) return -1;
    clear_field(field);
    render(*field, *player);
    destroy_field(field);
    free(bars);
    free(player);
    return 0;
}

int check_collision(Player player, Pos *bars) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 2; j++) {
            if (player.pos[j][0].x >= bars[i].x && player.pos[j][0].x <= bars[i].x + 2 &&
                player.pos[j][0].y == bars[i].y && player.direction == -1) {
                return 1;
            }
        }
    }
    return 0;
}

void update_bars(Field *field, Pos *bars) {
    for (int i = 0; i < 20; i++) {
        if (bars[i].y >= 0 && bars[i].y < field->height) {
            field->cells[bars[i].x][bars[i].y] = '-';
            field->cells[bars[i].x + 1][bars[i].y] = '-';
            field->cells[bars[i].x + 2][bars[i].y] = '-';
        }
    }
}

void render(Field field, Player player) {
    printf("\n");
    update_player(field, player);
    for (int i = field.height - 1; i >= 0; i--) {
        for (int j = 0; j < field.width; j++) {
            printf("%c", field.cells[j][i]);
        }
        printf("\n");
    }
    printf("     Health: %d/%d  |  Score: %d\n", player.health, player.max_health, player.score);
}