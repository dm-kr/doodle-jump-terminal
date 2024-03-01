#include "list.h"

#include <stdio.h>
#include <stdlib.h>

node_t *init(int x, int y) {
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->x = x;
    node->y = y;
    node->next = NULL;
    return node;
}

void add(node_t *head, node_t *node) {
    if (head == NULL) {
        head = node;
    } else {
        node->next = head;
        head = node;
    }
}

void destroy(node_t *head) {
    node_t *tmp = head;
    while (tmp != NULL) {
        node_t *tmp_next = tmp->next;
        free(tmp);
        tmp = tmp_next;
    }
}