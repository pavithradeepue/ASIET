#include <stdio.h>
int n, m;
int alloc[10][10], max[10][10], avail[10], need[10][10];
int work[10], finish[10], safeSeq[10];

void calculateNeed() 
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

int isSafe() 
{
    for (int i = 0; i < m; i++) work[i] = avail[i];
    for (int i = 0; i < n; i++) finish[i] = 0;

    int count = 0;
    while (count < n) 
    {
        int found = 0;
        for (int i = 0; i < n; i++) 
        {
            if (!finish[i]) 
            {
                int canExecute = 1;
                for (int j = 0; j < m; j++) 
                {
                    if (need[i][j] > work[j]) 
                    {
                        canExecute = 0;
                        break;
                    }
                }
                if (canExecute) 
                {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0; 
    }
    return 1; 
}

void requestResources() 
{
    int pid, req[10];
    printf("\nEnter process number requesting resources: ");
    scanf("%d", &pid);
    printf("Enter requested resources: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &req[i]);
    }
    for (int i = 0; i < m; i++) 
    {
        if (req[i] > need[pid][i]) 
        {
            printf("Error: Process exceeded its maximum claim.\n");
            return;
        }
        if (req[i] > avail[i]) 
        {
            printf("Resources unavailable. Process must wait.\n");
            return;
        }
    }
    for (int i = 0; i < m; i++) 
    {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
    }
    if (isSafe()) 
    {
        printf("Request granted. System remains in a safe state.\n");
    } 
    else 
    {
        for (int i = 0; i < m; i++) 
        {
            avail[i] += req[i];
            alloc[pid][i] -= req[i];
            need[pid][i] += req[i];
        }
        printf("Request denied. System would enter an unsafe state.\n");
    }
}

void display() 
{
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("\n");
    }
    printf("\nMax Matrix:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
    printf("\nAvailable Resources: ");
    for (int i = 0; i < m; i++)
    {
        printf("%d ", avail[i]);
    }
    printf("\n");
}

int main() 
{
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    printf("Enter max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    calculateNeed();

    if (isSafe()) 
    {
        printf("\nSystem is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    }  
    else 
    {
        printf("\nSystem is in an unsafe state.\n");
        return 0;
    }
    display();
    requestResources();
    return 0;
}
