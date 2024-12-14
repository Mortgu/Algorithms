#ifndef ALGORITHMS_SKIPLIST_H
#define ALGORITHMS_SKIPLIST_H

#define MAX_LEVEL 6

typedef struct SkipNode {
    int key, height;
    struct SkipNode** forward; // Nächsten Nodes auf Ebene
} SkipNode;

typedef struct SkipList {
    int level;
    struct SkipNode *header;
} SkipList;

SkipList* createList();
int search(SkipList* list, int key);
void insert(SkipList* list, int key);
void delete(SkipList* list, int key);

SkipNode* createNode(int key, int level);
int randomLevel();
void print(SkipList* list);

#endif