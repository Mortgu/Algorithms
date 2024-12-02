#include <stdio.h>

void SelectionSort(int a[], int n);
void printArray(int a[], int n);

int main(int argc, char* argv[]) {
    int array[] = {9, 23, 1, 34, 12, 99, 34, 6, 0, 8};

    printf("Unsorted array: ");
    printArray(array, 10);
    SelectionSort(array, 10);
    printf("Sorted array: ");
    printArray(array, 10);

    return 0;
}

void SelectionSort(int a[], int n) {
    for (int i = 0; i < n; i++) {
        int min = i;

        for (int j = i; j < n; j++) {
            if (a[j] < a[min]) min = j;
        }

        int h = a[i];
        a[i] = a[min];
        a[min] = h;
    }
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%i ", a[i]);
    }
    printf("\n");
}