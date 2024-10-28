/*PAVITHRA DEEPU E
CSE AI S3 47
POSTFIX EVALUATION*/

#include <stdio.h>

float stack[100];
int top = -1;

void push(float value) {
    stack[++top] = value;
}

float pop() {
    return stack[top--];
}

float evaluatePostfix(char* expression) {
    for (int i = 0; expression[i]; i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            float val = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                val = val * 10 + (expression[i] - '0');
                i++;
            }
            push(val);
            i--;
        } else if (expression[i] == '+' || expression[i] == '-' || 
                   expression[i] == '*' || expression[i] == '/') {
            float val2 = pop();
            float val1 = pop();
            switch (expression[i]) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': push(val1 / val2); break;
            }
        }
    }
    return pop();
}

int main() {
    char expression[100];
    printf("Enter a postfix expression: ");
    fgets(expression, sizeof(expression), stdin);
    printf("Result: %.2f\n", evaluatePostfix(expression));
    return 0;
}
