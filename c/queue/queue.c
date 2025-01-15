#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

int main(int argc, char *argv[]) {
  return 0;
}

void initializeQueue(Queue* queue) {
  queue->front = -1;
  queue->rear = 0;
}

bool isEmpty(const Queue* queue) {
  return (queue->front == queue->rear -1);
}

bool isFull(const Queue* queue) {
  return (queue->rear == MAX_QUEUE_SIZE);
}


void enqueue(Queue* queue, Node* node) {
  if (isFull(queue)) {
    printf("Queue is full\n");
    return;
  }

  queue->items[queue->rear] = *node;
  queue->rear++;
}

void dequeue(Queue* queue) {
  if (isEmpty(queue)) {
    printf("Queue is empty\n");
    return;
  }

  queue->front++;
}

Node* peek(Queue* queue) {
  if (isEmpty(queue)) {
    printf("Queue is empty\n");
    return NULL;
  }

  return &(queue->items[queue->front + 1]);
}

void print_queue(Queue* queue) {
  if (isEmpty(queue)) {
    printf("Queue is empty\n");
    return;
  }

  printf("Current Queue: ");
  for (int i = queue->front + 1; i < queue->rear; i++) {
    printf("%d ", queue->items[i].value);
  }

  printf("\n");
}

