#include <stdio.h>

void InsertionSort(int a[], int n);
void printArray(int a[], int n);

int main(int argc, char* argv[]) {
    int array[] = {9, 23, 1, 34, 12, 99, 34, 6, 0, 8};

    printf("Unsorted array: ");
    printArray(array, 10);
    InsertionSort(array, 10);
    printf("Sorted array: ");
    printArray(array, 10);

    return 0;
}

void InsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int prev = i - 1;

        while (prev >= 0 && a[prev] > key) {
            a[prev + 1] = a[prev];
            prev = prev - 1;
        }

        a[prev + 1] = key;
    }
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%i ", a[i]);
    }
    printf("\n");
}