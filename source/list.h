#ifndef _LIST_H_
#define _LIST_H_

typedef struct node {
    int x;
    int y;
    struct node *next;
} node_t;

node_t *init(int x, int y);
void add(node_t *head, node_t *node);
void destroy(node_t *head);

#endif