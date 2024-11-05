/*Pavithra Deepu E
CSE AI S3
47
Program to implement a Hash Table*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

struct DataItem {
    int data;
    int key;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
    return key % SIZE;
}

struct DataItem* search(int key) {
    int hashIndex = hashCode(key);
    while (hashArray[hashIndex] != NULL) {
        if (hashArray[hashIndex]->key == key) {
            return hashArray[hashIndex];
        }
        ++hashIndex;
        hashIndex %= SIZE;
    }
    return NULL;
}

void insert(int key, int data) {
    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    int hashIndex = hashCode(key);

    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        ++hashIndex;
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = item;
}

struct DataItem* delete(struct DataItem* item) {
    int key = item->key;
    int hashIndex = hashCode(key);

    while (hashArray[hashIndex] != NULL) {
        if (hashArray[hashIndex]->key == key) {
            struct DataItem* temp = hashArray[hashIndex];
            hashArray[hashIndex] = dummyItem;
            return temp;
        }
        ++hashIndex;
        hashIndex %= SIZE;
    }

    return NULL;
}

void display() {
    int i;
    for (i = 0; i < SIZE; i++) {
        if (hashArray[i] != NULL) {
            printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
        } else {
            printf(" ~~ ");
        }
    }
    printf("\n");
}

int main() {
    int choice, key, data;
    dummyItem = (struct DataItem*)malloc(sizeof(struct DataItem));
    dummyItem->data = -1;
    dummyItem->key = -1;

    // Main menu loop
    while (1) {
        printf("\nHash Table Operations:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  // Insert
                printf("Enter key and data to insert: ");
                scanf("%d %d", &key, &data);
                insert(key, data);
                break;

            case 2:  // Search
                printf("Enter key to search: ");
                scanf("%d", &key);
                item = search(key);
                if (item != NULL) {
                    printf("Element found: %d\n", item->data);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 3:  // Delete
                printf("Enter key to delete: ");
                scanf("%d", &key);
                item = search(key);
                if (item != NULL) {
                    delete(item);
                    printf("Element with key %d deleted\n", key);
                } else {
                    printf("Element not found to delete\n");
                }
                break;

            case 4:  // Display
                printf("Hash Table:\n");
                display();
                break;

            case 5:  // Exit
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
