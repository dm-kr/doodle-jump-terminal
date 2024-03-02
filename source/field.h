#ifndef _FIELD_H_
#define _FIELD_H_

typedef struct Field {
    int width;
    int height;
    char **cells;
} Field;

Field *create_field(int width, int height);
void clear_field(Field *field);
void destroy_field(Field *field);

#endif