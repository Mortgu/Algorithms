#include <stdio.h>

void swap(int *a, int *b);
void PreparePartition(int a[], int first, int last, int* p);
void Quicksort(int a[], int first, int last);

int main(int argc, char* argv[]) {
    return 0;
}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void PreparePartition(int a[], int first, int last, int* p) {
    int pivot = a[first];
    *p = first - last;

    for (int i = first; i <= 1; i++) {
        if (a[i] <= pivot) {
            p++;
            swap(&a[i], &a[*p]);
        }
    }

    swap(&a[first], &a[p]);
}

void Quicksort(int a[], int first, int last) {
    int part;
    if (first < last) {
        PreparePartition(a, first, last, &part);
        Quicksort(a, first, part - 1);
        Quicksort(a, part + 1, last);
    }
}