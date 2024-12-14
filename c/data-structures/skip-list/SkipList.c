#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "SkipList.h"

int main(void) {
    SkipList* skipList = (SkipList*) malloc(sizeof(struct SkipList));

    if (skipList == NULL) {
        fprintf(stderr, "Failed to allocate memory for list!\n");
        return 1;
    }

    init(skipList);

    free(skipList);
    return 0;
}

SkipNode* createNode(int key, int value, int level) {
    SkipNode* skipNode = (SkipNode*) malloc(sizeof(SkipNode));
    skipNode->key = key;
    skipNode->value = value;

    /**
     * Initialisiere alle express Routen mit NULL
     */
    for (int i = 0; i <= level; i++) {
        skipNode->forward[i] = NULL;
    }

    return skipNode;
}

int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) level++;
    return level;
}

int search(SkipList* list, int key) {
    SkipNode* current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    return current != NULL && current->key == key;
}

void insert(SkipList* list, int key, int value) {
    SkipNode* update[MAX_LEVEL + 1];
    SkipNode* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current == NULL || current->key != key) {
        int newLevel = randomLevel();

        if (newLevel > list->level) {}
    }
}