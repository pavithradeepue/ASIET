#include <stdio.h>

int main()
{
    int i, j, r, c, r1, c1, k = 0, n = 0, n2 = 0;
    int a[100][100], b[100][100];
    int T1[100][3], T2[100][3], R[100][3];

    printf("Enter the number of rows of the First matrix: ");
    scanf("%d", &r);
    printf("Enter the number of columns of the First matrix: ");
    scanf("%d", &c);
    printf("Enter the number of rows of the second matrix: ");
    scanf("%d", &r1);
    printf("Enter the number of columns of the second matrix: ");
    scanf("%d", &c1);

    if (r != r1 || c != c1) {
        printf("Error: Matrices must be of the same dimensions for addition.\n");
        return 1;
    }

    printf("Enter the First matrix elements:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter the second matrix elements:\n");
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c1; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    k = 1;
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (a[i][j] != 0) {
                T1[k][0] = i;
                T1[k][1] = j;
                T1[k][2] = a[i][j];
                k++;
                n++;
            }
        }
    }
    
    T1[0][0] = r;
    T1[0][1] = c;
    T1[0][2] = n;

    k = 1;
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c1; j++) {
            if (b[i][j] != 0) {
                T2[k][0] = i;
                T2[k][1] = j;
                T2[k][2] = b[i][j];
                k++;
                n2++;
            }
        }
    }
    T2[0][0] = r1;
    T2[0][1] = c1;
    T2[0][2] = n2;

    
    k = 0;
    int p1 = 1, p2 = 1;

    while (p1 <= n && p2 <= n2) {
        if (T1[p1][0] == T2[p2][0] && T1[p1][1] == T2[p2][1]) {
            R[k][0] = T1[p1][0];
            R[k][1] = T1[p1][1];
            R[k][2] = T1[p1][2] + T2[p2][2];
            p1++;
            p2++;
        } else if (T1[p1][0] < T2[p2][0] || (T1[p1][0] == T2[p2][0] && T1[p1][1] < T2[p2][1])) {
            R[k][0] = T1[p1][0];
            R[k][1] = T1[p1][1];
            R[k][2] = T1[p1][2];
            p1++;
        } else {
            R[k][0] = T2[p2][0];
            R[k][1] = T2[p2][1];
            R[k][2] = T2[p2][2];
            p2++;
        }
        k++;
    }


    while (p1 <= n) {
        R[k][0] = T1[p1][0];
        R[k][1] = T1[p1][1];
        R[k][2] = T1[p1][2];
        p1++;
        k++;
    }

    while (p2 <= n2) {
        R[k][0] = T2[p2][0];
        R[k][1] = T2[p2][1];
        R[k][2] = T2[p2][2];
        p2++;
        k++;
    }

    printf("The Sparse matrix representation of the Resultant matrix is:\n");
    printf("Row\tColumn\tValue\n");
    for (i = 0; i < k; i++) {
        printf("%d\t%d\t%d\n", R[i][0], R[i][1], R[i][2]);
    }

    return 0;
}
