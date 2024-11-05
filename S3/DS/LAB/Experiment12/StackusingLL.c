/*Pavithra Deepu E
S3 CSE AI
47
Program for implementation of stack using Linked List.*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Struct representing a node in the linked list
typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

// Function to create a new node with the given data
Node* createNode(int new_data) 
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

typedef struct Stack 
{
    Node* head;
} Stack;

void initializeStack(Stack* stack) 
{
    stack->head = NULL;
}

int isEmpty(Stack* stack) 
{
    return stack->head == NULL;
}

void push(Stack* stack, int new_data) 
{
    Node* new_node = createNode(new_data);
    
   if (!new_node) 
   {
        printf("\nStack Overflow");
        return;
   }
    
    new_node->next = stack->head;
    stack->head = new_node;
}

void pop(Stack* stack) 
{
   if (isEmpty(stack)) 
   {
        printf("\nStack Underflow\n");
        return;
   } 
   else 
   {
        Node* temp = stack->head;
        stack->head = stack->head->next;
        free(temp);
    }
}

int peek(Stack* stack) 
{
    if (!isEmpty(stack))
        return stack->head->data;
    else
    {
        printf("\nStack is empty");
        return INT_MIN;
    }
}

int main() 
{
    Stack stack;
    initializeStack(&stack);
    
    int choice, value;
    
    while (1) 
    {
        // Display menu
        printf("\nStack Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Check if Stack is Empty\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1: // Push
                printf("Enter the value to push onto the stack: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
                
            case 2: // Pop
                pop(&stack);
                break;
                
            case 3: // Peek
                value = peek(&stack);
                if (value != INT_MIN) {
                    printf("Top element is %d\n", value);
                }
                break;
                
            case 4: // Check if stack is empty
                if (isEmpty(&stack)) 
                {
                    printf("The stack is empty.\n");
                } 
                else 
                {
                    printf("The stack is not empty.\n");
                }
                break;
                
            case 5: // Exit
                printf("Exiting the program.\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
