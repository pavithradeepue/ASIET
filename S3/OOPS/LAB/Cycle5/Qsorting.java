/* Pavithra Deepu E
S3 CSE-AI 47
Java program to perform Quick Sorting */

import java.util.*;

class QuickSorter {
    int partition(int array[], int start, int end) {
        int pivot = array[end];
        int index = start - 1;

        for (int j = start; j < end; j++) {
            if (array[j] < pivot) {
                index++;
                int temp = array[index];
                array[index] = array[j];
                array[j] = temp;
            }
        }

        int temp = array[index + 1];
        array[index + 1] = array[end];
        array[end] = temp;

        return index + 1;
    }

    void quickSort(int array[], int start, int end) {
        if (start < end) {
            int partitionIndex = partition(array, start, end);
            quickSort(array, start, partitionIndex - 1);
            quickSort(array, partitionIndex + 1, end);
        }
    }
}

class Qsorting {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        QuickSorter sorter = new QuickSorter();

        int numbers[] = new int[100];
        System.out.println("Enter the length of the array:");
        int length = scanner.nextInt();

        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < length; i++) {
            numbers[i] = scanner.nextInt();
        }

        sorter.quickSort(numbers, 0, length - 1);

        System.out.println("The sorted array is:");
        for (int i = 0; i < length; i++) {
            System.out.print(numbers[i] + " ");
        }
        System.out.println();

        scanner.close();
    }
}
