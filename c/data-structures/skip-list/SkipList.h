#ifndef ALGORITHMS_SKIPLIST_H
#define ALGORITHMS_SKIPLIST_H

#define MAX_LEVEL 6

typedef struct SkipNode {
    int key, value;
    struct SkipNode *forward[]; // Express routes L1, L2, ...
} SkipNode;

typedef struct SkipList {
    int level;
    struct SkipNode *header;
} SkipList;

SkipList* createList();
int search(SkipList* list, int key);
void insert(SkipList* list, int key, int value);

SkipNode* createNode(int key, int value, int level);
int randomLevel();
void print(SkipList* list);

#endif