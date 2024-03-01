#include "render.h"

#include <stdio.h>

void render(Field field, Player player) {
    printf("\n");
    update_player(&field, &player);
    for (int i = field.height - 1; i >= 0; i--) {
        for (int j = 0; j < field.width; j++) {
            printf("%c", field.cells[j][i]);
        }
        printf("\n");
    }
    printf("     Health: %d/%d  |  Score: %d\n", player.health, player.max_health, player.score);
}