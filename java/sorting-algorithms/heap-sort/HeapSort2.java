import java.util.Arrays;

class Main {

    // MergeSort
    public static void mergeSort(int[] array, int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);
            merge(array, left, mid, right);
        }
    }

    public static void merge(int[] array, int left, int mid, int right) {
        int[] temp = new int[right - left + 1];
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            temp[k++] = (array[i] < array[j]) ? array[i++] : array[j++];
        }
        while (i <= mid) temp[k++] = array[i++];
        while (j <= right) temp[k++] = array[j++];

        System.arraycopy(temp, 0, array, left, temp.length);
        System.out.println("Merge step: " + Arrays.toString(array));
    }

    // HeapSort
    public static void heapSort(int[] array) {
        int n = array.length;

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(array, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            int temp = array[0];
            array[0] = array[i];
            array[i] = temp;

            heapify(array, i, 0);
            System.out.println("Heap step: " + Arrays.toString(array));
        }
    }

    public static void heapify(int[] array, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && array[left] > array[largest]) largest = left;
        if (right < n && array[right] > array[largest]) largest = right;

        if (largest != i) {
            int swap = array[i];
            array[i] = array[largest];
            array[largest] = swap;

            heapify(array, n, largest);
        }
    }

    public static void main(String[] args) {
        int[] array1 = {-5, 13, -32, 7, -3, 17, 23, 12, -35, 19};
        int[] array2 = array1.clone();

        System.out.println("Original array: " + Arrays.toString(array1));
        mergeSort(array1, 0, array1.length - 1);
        System.out.println("Sorted by MergeSort: " + Arrays.toString(array1));

        System.out.println("\nOriginal array: " + Arrays.toString(array2));
        heapSort(array2);
        System.out.println("Sorted by HeapSort: " + Arrays.toString(array2));
    }
}