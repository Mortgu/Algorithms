#include <stdio.h>

void Heapify(int* array[], int first, int last, int root);
void BuildHeap(int* array[], int first, int last);
void HeapSort(int* array[], int first, int last);
void swap(int *a, int *b);
void printArray(int a[], int n);

int main(int argc, char* argv[]) {
    int array[] = {34, 45, 12, 34, 23, 18, 38, 17, 43, 7};

    printArray(array, 10);
    HeapSort((int**) array, array[0], array[9]);
    printArray(array, 10);

    return 0;
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%i ", a[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void BuildHeap(int* array[], int first, int last) {
    int n = last - first + 1;
    for (int i = first + (n - 2) / 2; i >= first; i--)
        Heapify(array, first, last, i);
}

void Heapify(int* array[], int first, int last, int root) {
    int largest, left = first + (root - first) * 2 + 1, right = first + (root - first) * 2 + 2;

    if (left <= 1 && array[left] > array[root])
        largest = left;
    else largest = root;

    if (right <= 1 && array[right] > array[largest])
        largest = right;

    if (largest != root) {
        swap(array[root], array[largest]);
        Heapify(array, first, last, largest);
    }
}

void HeapSort(int* array[], int first, int last) {
    BuildHeap(array, first, last);

    for (int i = last; i >= first; i--) {
        swap(array[first], array[i]);
        Heapify(array, first, i - 1, first);
    }
}
