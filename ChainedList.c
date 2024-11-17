#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Product {
    char name[50];
    int price;
    struct Product *next;
};

struct Product* getTail(struct Product* cur) {
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }
    return cur;
}

void swap(struct Product* a, struct Product* b) {
    char tempName[50];
    int tempPrice;

    strcpy(tempName, a->name);
    tempPrice = a->price;

    strcpy(a->name, b->name);
    a->price = b->price;

    strcpy(b->name, tempName);
    b->price = tempPrice;
}

struct Product* partition(struct Product* head, struct Product* end, struct Product** newHead, struct Product** newEnd) {
    struct Product* pivot = end;
    struct Product* prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->price < pivot->price) {
            if ((*newHead) == NULL) {
                (*newHead) = cur;
            }
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) {
                prev->next = cur->next;
            }
            struct Product* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL) {
        (*newHead) = pivot;
    }

    (*newEnd) = tail;

    return pivot;
}

struct Product* quickSortRecur(struct Product* head, struct Product* end) {
    if (!head || head == end) {
        return head;
    }

    struct Product *newHead = NULL, *newEnd = NULL;

    struct Product* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        struct Product* tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(struct Product** headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}

void printList(struct Product* node) {
    while (node != NULL) {
        printf("name: %-7s\tprice: %i\n", node->name, node->price);
        node = node->next;
    }
}

void generateRandomArray(struct Product* head, char produktNamen[][50], int array_size) {
    struct Product* current = head;
    srand(time(NULL));

    for (int i = 0; i < array_size; i++) {
        strcpy(current->name, produktNamen[i]);
        current->price = rand() % (65 + 1 - 0) + 0;
        if (i < array_size - 1) {
            current->next = malloc(sizeof(struct Product));
        } else {
            current->next = NULL;
        }
        current = current->next;
    }
}

int main() {
    char produktNamen[][50] = {"Apfel", "Banane", "Orange", "Mango", "Traube"};
    int array_size = sizeof(produktNamen) / sizeof(produktNamen[0]);

    struct Product* head = malloc(sizeof(struct Product));
    generateRandomArray(head, produktNamen, array_size);

    printf("Unsorted List:\n");
    printList(head);

    quickSort(&head);

    printf("\nSorted List:\n");
    printList(head);

    return 0;
}