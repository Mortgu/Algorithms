#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 100

typedef struct Node {
    int value, color, dist;
    struct Node* pred;
} Node;

typedef struct {
    Node items[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void initialize_queue(Queue* queue);

bool is_empty(Queue* queue);
bool is_full(Queue* queue);

void enqueue(Queue* queue, Node* node);
void dequeue(Queue* queue);
void print_queue(Queue* queue);

Node* peek(Queue* queue);

#endif
