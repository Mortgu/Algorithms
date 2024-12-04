#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int number;
    struct Node* next;
} Node;

Node* createNode(int number) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->number = number;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(Node** head, int number) {
    Node* newNode = createNode(number);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void deleteNode(Node** head, Node* delNode) {
    if (*head == NULL || delNode == NULL) return;

    if (*head == delNode) {
        *head = delNode->next;
    }

    Node* temp = *head;
    while (temp->next != delNode) {
        temp = temp->next;
    }
    temp->next = delNode->next;
    free(delNode);
}

void printList(Node* head) {
    if (head == NULL) return;
    Node* temp = head;
    do {
        printf("%d ", temp->number);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    Node* head = NULL;
    for (int i = 1; i <= 49; i++) {
        insertEnd(&head, i);
    }

    srand(time(0));
    for (int i = 0; i < 6; i++) {
        int steps = rand() % (49 - i);
        Node* temp = head;
        for (int j = 0; j < steps; j++) {
            temp = temp->next;
        }
        printf("Selected number: %d\n", temp->number);
        deleteNode(&head, temp);
    }

    return 0;
}