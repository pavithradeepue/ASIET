#include <stdio.h>

void main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[100], at[100], bt[100], ct[100], tt[100], wt[100], rt[100];
    int i, j, temp, time = 0, completed = 0;
    float avg_wt = 0, avg_tt = 0;

    for (i = 0; i < n; i++) 
    {
        printf("Enter the Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter the Process Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter the Process Burst time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; 
    }


    while (completed < n) 
    {
        int selected_process = -1;
        int shortest_burst_time = 10000;  
      
        for (i = 0; i < n; i++) 
        {
            if (rt[i] > 0 && at[i] <= time && rt[i] < shortest_burst_time) 
            {
                shortest_burst_time = rt[i];
                selected_process = i;
            }
        }

      
        if (selected_process != -1) 
        {
            rt[selected_process]--;  
            time++;
            if (rt[selected_process] == 0) 
            {
                completed++;  
                ct[selected_process] = time;  // Completion time
                tt[selected_process] = ct[selected_process] - at[selected_process];  // Turnaround time
                wt[selected_process] = tt[selected_process] - bt[selected_process];  // Waiting time
            }
        } 
        else
        {
            time++; 
        }
    }

    for (i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }

    avg_wt /= n;
    avg_tt /= n;

    printf("-------------------------------------------------------------------------------------------\n");
    printf("Process Id\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    printf("-------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) 
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
   
    }

    printf("-------------------------------------------------------------------------------------------\n");
    printf("\nAverage Turn Around Time: %.2f\n", avg_tt);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    
    printf("Gantt Chart\n");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0;i<n;i++)
	{
		printf("|\tP%d\t|",pid[i]);
	}
	printf("\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("0\t\t");
	for(int i=0;i<n;i++)
	{
		printf("%d\t\t",ct[i]);
	}
	printf("\n");
	
	//Print Gantt Chart
    printf("\nGANTT CHART\n");
    printf("____________________________________________________________________________________ \n");
    for (i = 0; i < n; i++) {
        printf("|  %d  ", pid[i]);
    }
    printf("|\n");
    printf("____________________________________________________________________________________ \n");
    for (i = 0; i < n; i++) {
        printf("%d        ", at[i]);
    }
    printf("\n");


}
