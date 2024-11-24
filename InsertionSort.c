#include <stdio.h>
#include <stdlib.h>

int* insertion(int *array);
int min(int a, int b);
void switchPosition(int *a, int *b);
void printList(int *array) {
    for (int i = 0; i < 11; i++) {
        printf("%i\n", array[i]);
    }
}

int main(int argc, char** argv) {
    int array[] = {100, 20, 1, 40, 293, 93, 8, 4, 12, 32, 75};
    insertion(array);

    printList(array);

    return 0;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void switchPosition(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* insertion(int *array) {
    for (int i = 1; i < 11; i++) {
        int key = array[i];
        int index = i - 1;

        while (index >= 0 && key > array[index]) {
            switchPosition(&array[index], &key);
            printf("%i > %i\n", key, array[index]);
            index--;
        }

        array[index + 1] = key;
    }

    return NULL;
}

