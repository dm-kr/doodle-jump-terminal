#include "bars.h"

#include <stdlib.h>
#include <time.h>

Bars *create_bars(int bars_amount) {
    Bars *bars = (Bars *)malloc(sizeof(Bars));
    bars->bars = (Pos *)malloc(sizeof(Pos) * bars_amount);
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        bars->bars[i].x = (rand() / 2) % 26 + 1;
        bars->bars[i].y = 3 * i + 2;
    }
    return bars;
}

void update_bars(Field *field, Bars *bars) {
    for (int i = 0; i < 20; i++) {
        if (bars->bars[i].y >= 0 && bars->bars[i].y < field->height) {
            field->cells[bars->bars[i].x][bars->bars[i].y] = '-';
            field->cells[bars->bars[i].x + 1][bars->bars[i].y] = '-';
            field->cells[bars->bars[i].x + 2][bars->bars[i].y] = '-';
        }
    }
}

void move_bars(Field *field, Bars *bars) {
    for (int i = 0; i < 20; i++) {
        bars->bars[i].y--;
        if (bars->bars[i].y < 0) {
            bars->bars[i].y += 60;
            bars->bars[i].x = (rand() / 2) % 26 + 1;
        }
    }
}

int check_bars_collision(Player player, Bars *bars) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 2; j++) {
            if (player.pos[j][0].x >= bars->bars[i].x && player.pos[j][0].x <= bars->bars[i].x + 2 &&
                player.pos[j][0].y == bars->bars[i].y && player.direction == -1) {
                return 1;
            }
        }
    }
    return 0;
}

void destroy_bars(Bars *bars) {
    free(bars->bars);
    free(bars);
}