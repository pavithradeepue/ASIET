#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_CART 50

// Item structure
typedef struct {
    char name[20];
    float price;
    int quantity;
} Item;

Item stock[MAX_ITEMS] = {
    {"apple", 0.5, 100},
    {"banana", 0.2, 150},
    {"grapes", 1.5, 200}
};
int stock_size = 3;

// Cart structure
typedef struct {
    char name[20];
    int quantity;
} CartItem;

CartItem cart[MAX_CART];
int cart_size = 0;

// Function to display stock items
void display_stock() {
    printf("\nStock:\n");
    for (int i = 0; i < stock_size; i++) {
        printf("%s - $%.2f - %d in stock\n", stock[i].name, stock[i].price, stock[i].quantity);
    }
}

// Binary search function to find an item in stock
int find_item(char *name) {
    int left = 0, right = stock_size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(stock[mid].name, name);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Function to add an item to the cart
void add_to_cart() {
    char item_name[20];
    int quantity;
    
    printf("Enter item name: ");
    scanf("%s", item_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    int index = find_item(item_name);
    if (index != -1 && stock[index].quantity >= quantity) {
        // Add to cart
        strcpy(cart[cart_size].name, item_name);
        cart[cart_size].quantity = quantity;
        cart_size++;
        printf("Added %d of %s to the cart.\n", quantity, item_name);
    } else {
        printf("Item is out of stock or insufficient quantity.\n");
    }
}

// Function to checkout and generate bill
void checkout() {
    float total = 0.0;

    printf("\n--- Bill ---\n");
    for (int i = 0; i < cart_size; i++) {
        int index = find_item(cart[i].name);
        if (index != -1) {
            float cost = cart[i].quantity * stock[index].price;
            total += cost;
            stock[index].quantity -= cart[i].quantity;
            printf("%s x %d - $%.2f\n", cart[i].name, cart[i].quantity, cost);
        }
    }
    printf("Total bill: $%.2f\n", total);
    cart_size = 0; // Clear the cart after checkout
}

// Function to add or update stock items
void add_stock() {
    char item_name[20];
    float price;
    int quantity;

    printf("Enter item name: ");
    scanf("%s", item_name);
    printf("Enter price: ");
    scanf("%f", &price);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    int index = find_item(item_name);
    if (index != -1) {
        // Update existing item's quantity
        stock[index].quantity += quantity;
        printf("Updated %s quantity to %d.\n", stock[index].name, stock[index].quantity);
    } else {
        // Add a new item
        if (stock_size < MAX_ITEMS) {
            strcpy(stock[stock_size].name, item_name);
            stock[stock_size].price = price;
            stock[stock_size].quantity = quantity;
            stock_size++;
            printf("Added new item %s with quantity %d.\n", item_name, quantity);
        } else {
            printf("Stock is full, cannot add more items.\n");
        }
    }
}

// Main function
int main() {
    int choice;
    while (1) {
        printf("\nPOS System Menu:\n");
        printf("1. Add item to cart\n");
        printf("2. Checkout\n");
        printf("3. Display stock\n");
        printf("4. Add new stock\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_to_cart();
                break;
            case 2:
                checkout();
                break;
            case 3:
                display_stock();
                break;
            case 4:
                add_stock();
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
