#include <stdio.h>

void main() 
{
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int pid[100], at[100], bt[100], ct[100], tt[100], wt[100], rt[100];
    int i, time = 0, completed = 0;
    float avg_wt = 0, avg_tt = 0;

    // Input for processes, burst times, and arrival times
    for (i = 0; i < n; i++) {
        printf("Enter the Process PID: ");
        scanf("%d", &pid[i]);
        printf("Enter the Process Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter the Process Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Remaining burst time
    }

    // Main loop for Round Robin Scheduling
    while (completed < n) {
        int all_done = 1;

        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                all_done = 0;

                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                    printf("|  P%d  ", pid[i]);  // Print the process ID in Gantt chart
                } else {
                    time += rt[i];
                    ct[i] = time;
                    rt[i] = 0;  // Process completed
                    tt[i] = ct[i] - at[i];  // Turnaround time
                    wt[i] = tt[i] - bt[i];  // Waiting time
                    completed++;  // Process completed
                    printf("|  P%d  ", pid[i]);  // Print the process ID in Gantt chart
                }
            }
        }

        // If no process is ready to run, increment time
        if (all_done) {
            time++;
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tt += tt[i];
    }

    avg_wt /= n;
    avg_tt /= n;

    // Output results
    printf("\nPROCESS TABLE\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("| PID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("---------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n",
                pid[i], at[i], bt[i], ct[i], tt[i], wt[i]);
    }
    printf("------------------------------------------------------------\n");

    // Output the averages
    printf("\nAVERAGE WAITING TIME: %.2f\n", avg_wt);
    printf("AVERAGE TURNAROUND TIME: %.2f\n", avg_tt);

    // Print Gantt Chart (Finish the line)
    printf("\nGANTT CHART\n");
    printf("---------------------------------------------------------------------------------------\n");

    // Print process IDs in Gantt chart order (we've printed in the previous loop)
    printf("|\n");
    printf("---------------------------------------------------------------------------------------\n");

    // Print time in Gantt chart order (completion times)
    printf("0\t");
    time = 0; // Reset time to 0 to print completion times in the next loop
    for (i = 0; i < n; i++) 
    {
       
           printf("%d\t", ct[i]);
           time = ct[i];
        
    }
    printf("\n");
}

