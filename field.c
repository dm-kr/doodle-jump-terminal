#include "field.h"

#include <stdlib.h>

Field *create_field(int width, int height) {
    Field *field = (Field *)malloc(sizeof(Field));
    field->width = width;
    field->height = height;
    field->cells = (char **)malloc(sizeof(char *) * field->width);
    for (int i = 0; i < field->width; i++) {
        field->cells[i] = (char *)malloc(sizeof(char) * field->height);
    }
    for (int i = 0; i < field->width; i++) {
        for (int j = 0; j < field->height; j++) {
            field->cells[i][j] = '.';
        }
    }
    return field;
}

void clear_field(Field *field) {
    for (int i = 0; i < field->width; i++) {
        for (int j = 0; j < field->height; j++) {
            field->cells[i][j] = '.';
        }
    }
}

void destroy_field(Field *field) {
    for (int i = 0; i < field->width; i++) {
        free(field->cells[i]);
    }
    free(field->cells);
    free(field);
}