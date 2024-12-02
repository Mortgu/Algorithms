#include <stdio.h>

int BubbleSort(int a[], int n);
void printArray(int a[], int n);

int main(int argc, char* argv[]) {
    int array[] = {9, 23, 1, 34, 12, 99, 34, 6, 0, 8};

    printf("Unsorted array: ");
    printArray(array, 10);
    BubbleSort(array, 10);
    printf("Sorted array: ");
    printArray(array, 10);

    return 0;
}

int BubbleSort(int a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 2; j >= i; j--) {
            if (a[j] > a[j + 1]) {
                int h = a[j];
                a[j] = a[j + 1];
                a[j + 1] = h;
            }
        }
    }
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%i ", a[i]);
    }
    printf("\n");
}