#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "SkipList.h"

int main(void) {
    SkipList* skipList = createList();

    insert(skipList, 3);
    insert(skipList, 66);
    insert(skipList, 41);
    insert(skipList, 31);
    insert(skipList, 311);
    insert(skipList, 310);
    insert(skipList, 317);
    insert(skipList, 315);
    insert(skipList, 313);
    insert(skipList, 232);


    print(skipList);
    delete(skipList, 313);
    print(skipList);


    return 0;
}

SkipList* createList() {
    SkipList* skipList = (SkipList*) malloc(sizeof(SkipList));
    skipList->level = 0;
    skipList->header = createNode(INT_MIN, MAX_LEVEL);
    return skipList;
}

SkipNode* createNode(int key, int level) {
    SkipNode* skipNode = (SkipNode*) malloc(sizeof(SkipNode));

    skipNode->key = key;
    skipNode->height = level;
    skipNode->forward = (SkipNode**) malloc((level + 1) * sizeof(SkipNode*));

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

void insert(SkipList* list, int key) {
    SkipNode* update[MAX_LEVEL + 1]; // Speichert besuchte Knoten.
    SkipNode* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // current steht an dem Knoten 1 vor dem Knoten mit dem key welcher einen sprung kleiner ist als der gesuchte. (bzw dem danach einzufügenden)
    current = current->forward[0];

    if (current == NULL || current->key != key) {
        int newLevel = randomLevel();

        if (newLevel > list->level) {
            for (int i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header; // Zieht den header mit nach oben.
            }
            list->level = newLevel;
        }

        SkipNode* newNode = createNode(key, newLevel);

        // Nach dem einfügen eines Neuen Nodes, verlinkungen erkänzen.
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

void delete(SkipList* list, int key) {
    SkipNode* update[MAX_LEVEL + 1]; // Speichert besuchte Knoten.
    SkipNode* current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // current steht an dem Knoten 1 vor dem Knoten mit dem key welcher einen sprung kleiner ist als der gesuchte. (bzw dem danach einzufügenden)
    current = current->forward[0];

    if (current == NULL || current->key == key) {
        for (int i = 0; i <= current->height; i++) {
            if (update[i]->forward[i] != current) break;

            update[i]->forward[i] = current->forward[i];
        }

        free(current);
    }
}

void print(SkipList* list) {
    for (int i = list->level; i >= 0; i--) {
        SkipNode* current = list->header->forward[i];
        printf("Level %d: ", i);
        while (current != NULL) {
            printf("%d\t", current->key);
            current = current->forward[i];
        }
        printf("\n");
    }
}