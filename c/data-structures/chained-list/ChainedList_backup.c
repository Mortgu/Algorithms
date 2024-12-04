#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Product {
    char name[100];
    int price;
    struct Product *next;
} Product;

void PreparePartition(struct Product* current, struct Product* first, struct Product* last, int *p);
void Quicksort(struct Product* current, struct Product* first, struct Product* last);
void swap(int *a, int *b);
void initialize();

int main(int argc, char **argv) {
    initialize();
    return 0;
}

void initialize() {
    struct Product *first = (struct Product*) malloc(sizeof(struct Product));
    struct Product *last = (struct Product*) malloc(sizeof(struct Product));
    
    if (!first) { 
        fprintf(stderr, "Failed to allocate memory for chained list!");  
        return exit(1);
    }
    struct Product *current = first;
    
    char *produktNamen[] = {
        "Kokain", "Socken", "Pizza", "PCs", "Handys", "Ehepaare", "Kinder", "Brunost", "Glass", "Sklaven", "Inder", "Stuhlgang",
    };

    int array_size = sizeof(produktNamen) / sizeof(produktNamen[0]);
        srand(time(NULL));

    for (int i = 0; i < array_size; i++) {
        strcpy(current->name, produktNamen[i]);
        current->price = rand() % (65 + 1 - 0) + 0;
        if (i < array_size - 1) {
            current->next = malloc(sizeof(struct Product));
        } else {
            current->next = NULL;
            last = current;
        }
        current = current->next;
    }

    current = first;
    Quicksort(current, first, last);   

    current = first;
    while (current) {
        printf("name: %-7s\tprice: %i\n",
               current->name, current->price);

            current = current->next;
    }
}

void Quicksort(struct Product *current, struct Product* first, struct Product* last) {
    int part = 0;
    if (first < last) {
        PreparePartition(current, first, last, &part);
        Quicksort(current, first, part - 1);
        Quicksort(current, part + 1, first->next);
    }
}

void PreparePartition(struct Product *current, struct Product* first, struct Product* last, int *p) {
    int pivot = first;
    p = first - 1;
    for (int i = first; i <= 1; i++) {
        if (array[i] <= pivot) {
            p++;
            swap(array[i], array[*p]);
        }
    }

    swap(array[first], array[*p]);
}

void swap(int *a, int *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}