/*Pavithra Deepu E
S3 CSAI
Roll No 47
Program to print transpose of a matrix.*/

import java.util.*;
class transpose {
    Public static void main(String args[]) {
        Scanner S = new Scanner(System.in);
        int matrix[][] = new int[50][50];
        int transposematrix[][] = new int[50][50];
        int I, j;
        System.out.println(“Enter the number of rows:”);
        int row = S.nextInt();
        System.out.println(“Enter the number of columns:”);
        int column = S.nextInt();
        System.out.println(“Enter the elements of the matrix:”);
        for (I = 0; I < row; i++) {
            for (j = 0; j < column; j++) {
                matrix[i][j] = S.nextInt();
            }
        }
        for (i= 0; I < row; i++) {
            for (j = 0; j < column; j++) {
                transposematrix[j][i] = matrix[i][j];
            }
        }
        System.out.println(“The transpose of matrix is:”);
        for (I = 0; I < column; i++) {
            for (j = 0; j < row; j++) {
                System.out.print(transposematrix[i][j] + “ “);
            }
            System.out.println();
        }
        S.close();
    }
}
