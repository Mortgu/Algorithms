import java.util.Random;
import java.util.Arrays;

public class InsertionSort {

    public static void main(String[] args) {
        int n = 10000; // Startwert für n
        int[] array = new int[n];
        Random rand = new Random();

        // Generieren von gleichverteilten zufälligen ganzen Zahlen
        for (int i = 0; i < n; i++) {
            array[i] = rand.nextInt();
        }

        // Kopien des Arrays für verschiedene Sortieralgorithmen
        int[] arrayForBubbleSort = Arrays.copyOf(array, array.length);
        int[] arrayForQuickSort = Arrays.copyOf(array, array.length);
        int[] arrayForMergeSort = Arrays.copyOf(array, array.length);
        int[] arrayForInsertionSort = Arrays.copyOf(array, array.length);

        // Messen der Zeit für BubbleSort
        long startTime = System.currentTimeMillis();
        bubbleSort(arrayForBubbleSort, arrayForBubbleSort.length);
        long endTime = System.currentTimeMillis();
        long bubbleSortTime = endTime - startTime;

        // Messen der Zeit für QuickSort
        startTime = System.currentTimeMillis();
        quickSort(arrayForQuickSort, 0, arrayForQuickSort.length - 1);
        endTime = System.currentTimeMillis();
        long quickSortTime = endTime - startTime;

        // Messen der Zeit für MergeSort
        startTime = System.currentTimeMillis();
        mergeSort(arrayForMergeSort, 0, arrayForMergeSort.length - 1);
        endTime = System.currentTimeMillis();
        long mergeSortTime = endTime - startTime;

        // Messen der Zeit für InsertionSort
        startTime = System.currentTimeMillis();
        insertionSort(arrayForInsertionSort, arrayForInsertionSort.length);
        endTime = System.currentTimeMillis();
        long insertionSortTime = endTime - startTime;

        // Ausgabe der Ergebnisse
        System.out.println("BubbleSort Zeit: " + bubbleSortTime + " ms");
        System.out.println("QuickSort Zeit: " + quickSortTime + " ms");
        System.out.println("MergeSort Zeit: " + mergeSortTime + " ms");
        System.out.println("InsertionSort Zeit: " + insertionSortTime + " ms");

        // Berechnung der Anzahl der Zahlen, die in einer Minute sortiert werden können
        long oneMinuteInMillis = 60000;
        long bubbleSortNumbersPerMinute = (oneMinuteInMillis / bubbleSortTime) * n;
        long quickSortNumbersPerMinute = (oneMinuteInMillis / quickSortTime) * n;
        long mergeSortNumbersPerMinute = (oneMinuteInMillis / mergeSortTime) * n;
        long insertionSortNumbersPerMinute = (oneMinuteInMillis / insertionSortTime) * n;

        System.out.println("BubbleSort Zahlen pro Minute: " + bubbleSortNumbersPerMinute);
        System.out.println("QuickSort Zahlen pro Minute: " + quickSortNumbersPerMinute);
        System.out.println("MergeSort Zahlen pro Minute: " + mergeSortNumbersPerMinute);
        System.out.println("InsertionSort Zahlen pro Minute: " + insertionSortNumbersPerMinute);
    }

    public static void insertionSort(int a[], int n) {
        int i, j, key;

        for (j = 1; j < n; j++) {
            key = a[j];
            i = j - 1;

            while (i >= 0 && a[i] < key) {
                a[i+1] = a[i];
                i = i-1;
            }

            a[i+1] = key;
        } 
    }

    public static void insertionSortR(int a[], int n) {
        if (n <= 1) {
            return;
        }

        insertionSortR(a, n-1);

        int last = a[n-1];
        int j = n-2;

        while (j >= 0 && a[j] < last) {
            a[j+1] = a[j];
            j--;
        }

        a[j+1] = last;
    }

    public static void bubbleSort(int a[], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = n-2; j >= i; j--) {
                if (a[j] < a[j+1]) {
                    int h = a[j];
                    a[j] = a[j+1];
                    a[j+1] = h;
                }
            }
        }
    }

    public static void selectionSort(int a[], int n) {
        for (int i = 0; i < n-1; i++) {
            int maxIdx = i;
            for (int j = i+1; j < n; j++) {
                if (a[j] > a[maxIdx]) {
                    maxIdx = j;
                }
            }
            int temp = a[maxIdx];
            a[maxIdx] = a[i];
            a[i] = temp;
        }
    }

    public static void quickSort(int a[], int low, int high) {
        if (low < high) {
            int pivotIndex = partition(a, low, high);
            quickSort(a, low, pivotIndex - 1);
            quickSort(a, pivotIndex + 1, high);
        }
    }

    public static int partition(int a[], int low, int high) {
        Random rand = new Random();
        int pivotIndex = low + rand.nextInt(high - low + 1);
        int pivot = a[pivotIndex];
        swap(a, pivotIndex, high);
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (a[j] <= pivot) {
                i++;
                swap(a, i, j);
            }
        }
        swap(a, i + 1, high);
        return i + 1;
    }

    public static void swap(int a[], int i, int j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    public static void mergeSort(int a[], int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSort(a, left, mid);
            mergeSort(a, mid + 1, right);
            merge(a, left, mid, right);
        }
    }

    public static void merge(int a[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int[] L = new int[n1];
        int[] R = new int[n2];

        for (int i = 0; i < n1; i++) {
            L[i] = a[left + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = a[mid + 1 + j];
        }

        int i = 0, j = 0;
        int k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                a[k] = L[i];
                i++;
            } else {
                a[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            a[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            a[k] = R[j];
            j++;
            k++;
        }
    }
}
