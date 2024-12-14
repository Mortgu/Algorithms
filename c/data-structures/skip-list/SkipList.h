#ifndef ALGORITHMS_SKIPLIST_H
#define ALGORITHMS_SKIPLIST_H

#define MAX_LEVEL 6

typedef struct Node {
    int key, value;
    struct Node **forward;
} Node;

typedef struct List {
    struct Node *header;
    int level, size;
} List;

List* init(List* list);
void deinit();

int insert(List* list, int key, int value);

void delete(int key);
void search(int key);

void print();

static int rand_level();
static void dump(List *list);

#endif