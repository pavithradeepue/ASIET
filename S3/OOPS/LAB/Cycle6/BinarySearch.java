/* Pavithra Deepu E
S3 CSE AI 47
Program to perform Binary Search */

import java.util.*;

class BinarySearch {
    void searchElement(int array[], int target, int length) {
        int left = 0, right = length - 1;
        boolean found = false;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (array[mid] == target) {
                System.out.println("The element is found at index " + mid);
                found = true;
                break;
            } else if (array[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (!found) {
            System.out.println("The element is not found in the array.");
        }
    }
}

class BinarySearchDemo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        BinarySearch searcher = new BinarySearch();
        int array[] = new int[100];

        System.out.println("Enter the length of the array:");
        int length = scanner.nextInt();

        System.out.println("Enter the sorted array:");
        for (int i = 0; i < length; i++) {
            array[i] = scanner.nextInt();
        }

        System.out.println("Enter the search key:");
        int key = scanner.nextInt();

        searcher.searchElement(array, key, length);
        scanner.close();
    }
}
