#include <stdio.h>

int main() {
    int rows, cols, numNonZero1, numNonZero2;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter number of non-zero elements in matrix 1: ");
    scanf("%d", &numNonZero1);
    int mat1[100][3]; 

    printf("Enter non-zero elements of matrix 1 (row col value): \n");
    for (int i = 0; i < numNonZero1; i++) {
        scanf("%d %d %d", &mat1[i][0], &mat1[i][1], &mat1[i][2]);
    }

    printf("Enter number of non-zero elements in matrix 2: ");
    scanf("%d", &numNonZero2);
    int mat2[100][3]; 

    printf("Enter non-zero elements of matrix 2 (row col value): \n");
    for (int i = 0; i < numNonZero2; i++) {
        scanf("%d %d %d", &mat2[i][0], &mat2[i][1], &mat2[i][2]);
    }

    int result[200][3]; 
    int k = 0;

    for (int i = 0; i < numNonZero1; i++) {
        result[k][0] = mat1[i][0];
        result[k][1] = mat1[i][1];
        result[k][2] = mat1[i][2];
        k++;
    }

    for (int i = 0; i < numNonZero2; i++) {
        int found = 0;
        for (int j = 0; j < numNonZero1; j++) {
            if (mat2[i][0] == mat1[j][0] && mat2[i][1] == mat1[j][1]) {
                result[k-1][2] += mat2[i][2];
                found = 1;
                break;
            }
        }
        if (!found) {
            result[k][0] = mat2[i][0];
            result[k][1] = mat2[i][1];
            result[k][2] = mat2[i][2];
            k++;
        }
    }

    printf("Resulting sparse matrix: \n");
    for (int i = 0; i < k; i++) {
        printf("(%d, %d, %d)\n", result[i][0], result[i][1], result[i][2]);
    }

    return 0;
}

