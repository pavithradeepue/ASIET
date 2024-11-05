//Pavithra Deepu E
//S3 CSE AI
// 47
// C program for implementation of Insertion Sort

#include <stdio.h>

/* Function to sort array using insertion sort */
void insertionSort(int arr[], int n) 
{
    for (int i = 1; i < n; ++i) 
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n,i,arr[50];
    printf("Enter the no of elements in array:");
    scanf("%d", &n);
    
    printf("Enter the elements:");
    for(i = 0; i < n; i++)
    {
    	scanf("%d", &arr[i]);
    }    
    
    insertionSort(arr,n);
    printf("Sorted array is:");
    printArray(arr,n);

    return 0;
}

