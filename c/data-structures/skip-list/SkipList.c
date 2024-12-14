#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "SkipList.h"

int main(void) {
    List* list = (List*) malloc(sizeof(struct List));

    if (list == NULL) {
        fprintf(stderr, "Failed to allocate memory for list!\n");
        return 1;
    }

    init(list);

    // INSERT
    int arr[] = { 3, 6, 9, 2, 11, 1, 4 };
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        insert(list, arr[i], arr[i]);
    }
    dump(list);

    free(list);

    return 0;
}

List* init(List* list) {
    Node* header = (Node*) malloc(sizeof(Node));

    if (header == NULL) {
        fprintf(stderr, "Failed to allocate memory for header node!\n");
        return NULL;
    }

    list->header = header;

    header->key = INT_MAX;
    header->forward = (Node**) malloc(sizeof(Node*) * (MAX_LEVEL + 1));

    for (int i = 0; i <= MAX_LEVEL; i++) {
        header->forward[i] = list->header;
    }

    list->level = 1;
    list->size = 0;

    return list;
}

int insert(List* list, int key, int value) {
    Node* update[MAX_LEVEL + 1];
    Node* x = list->header;

    for (int i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[1];

    if (key == x->key) {
        x->value = value;
        return 0;
    } else {
        int level = rand_level();

        if (level > list->level) {
            for (int i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }

        x = (Node*) malloc(sizeof(struct Node));

        if (x == NULL) {
            fprintf(stderr, "Failed to allocate memory for x!\n");
            return 1;
        }

        x->key = key;
        x->value = value;
        x->forward = (Node**) malloc(sizeof(struct Node*) * (level + 1));

        if (x->forward == NULL) {
            fprintf(stderr, "Failed to allocate memory for x->forward!\n");
            return 1;
        }

        for (int i = 1; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }

    return 0;
}

static void dump(List *list) {
    Node *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}

static int rand_level() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}