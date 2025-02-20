#include <stdio.h>

void main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[100], at[100], bt[100], ct[100], tt[100], wt[100];
    int i, j, temp;
    float avg_wt = 0, avg_tt = 0;

    for (i = 0; i < n; i++) 
    {
        printf("Enter the Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter the Process Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter the Process Burst time: ");
        scanf("%d", &bt[i]); 
    }


    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - 1 - i; j++) 
        {
            if (at[j] > at[j + 1]) 
            {
                // Swap Arrival Time
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap Burst Time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap PID
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    ct[0] = at[0] + bt[0]; 
    for (i = 1; i < n; i++) 
    {
        ct[i] = ct[i - 1] + bt[i]; 
    }

    
    for (i = 0; i < n; i++) 
    {
        tt[i] = ct[i] - at[i]; 
        wt[i] = tt[i] - bt[i]; 
    }

    for (i = 0; i < n; i++) 
    {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }

    avg_wt /= n;
    avg_tt /= n;
    
    printf("------------------------------------------------------------------------------------------");
    printf("\nPROCESS TABLE\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("Process Id\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) 
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
  
    }
    printf("-------------------------------------------------------------------------------------------\n");

    printf("\nAVERAGE WAITING TIME: %.2f\n", avg_wt);
    printf("AVERAGE TURNAROUND TIME: %.2f\n", avg_tt);
     
    printf("Gantt Chart\n");
    	printf("-------------------------------------------------------------------------------------\n");
    	for(int i=0;i<n;i++)
	{
		printf("|\tP%d\t|",pid[i]);
	}
	printf("\n");
	printf("--------------------------------------------------------------------------------------\n");
	printf("0\t\t");
	for(int i=0;i<n;i++)
	{
		printf("%d\t\t",ct[i]);
	}
	printf("\n");

}
