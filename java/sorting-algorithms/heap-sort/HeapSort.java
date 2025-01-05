public class HeapSort {
    public static void main(String[] args) {
        int array[] = { 34, 45, 12, 34, 23, 18, 38, 17, 43, 7 };
        Heap_Sort(array, 0, array.length - 2);
    }

    public static void BuildHeap(int array[], int first, int last) {
        int n = last - first + 1;
        System.out.println("n=" + n);
        for (int i = first + (n - 2) / 2; i >= first; i--) {
            Heapify(array, first, last, i);
        }
    }

    public static void Heapify(int array[], int first, int last, int root) {
        int largest, left = first + (root - first) * 2 + 1, right = first + (root - first) * 2 + 2;
        System.out.println("root=" + root + ", left=" + left + ", right=" + right + ", array[" + left + "]=" + array[left] + ", array[" + right + "]=" + array[right]);

        if (left <= last && array[left] > array[right]) 
            largest = left;
        else largest = root; 

        if (right <= last && array[right] > array[largest]) 
            largest = right;

        if (largest != root) {
            int swap = array[root];
            array[root] = array[largest];
            array[largest] = swap;
            Heapify(array, first, last, largest);
        }
     }

     public static void Heap_Sort(int array[], int first, int last) {
        BuildHeap(array, first, last);

        for (int i = last; i > first; i--) {
            int temp = array[0];
            array[0] = array[i];
            array[i] = temp;

            Heapify(array, first, last - 1, i);
        }
     }
}
