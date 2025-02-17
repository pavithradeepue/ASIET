#include <stdio.h>

int main() {
    int n, at[10], bt[10], ct[10], wt[10], temp[10], tt[10], p[10];
    int smallest, count = 0, time, end = 0;
    double avg_wt = 0, avg_tt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the Arrival Time (AT) and Burst Time (BT) for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        temp[i] = bt[i];  
        p[i] = i + 1;   
    }

    bt[9] = 9999; 

    for (time = 0; count != n; time++) {
        smallest = 9;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && bt[i] < bt[smallest] && bt[i] > 0) {
                smallest = i;
            }
        }

        bt[smallest]--;

        if (bt[smallest] == 0) {
            count++;
            end = time + 1;
            ct[smallest] = end;  
            tt[smallest] = ct[smallest] - at[smallest];  
            wt[smallest] = tt[smallest] - temp[smallest]; 
        }
    }

    
    printf("Process Id\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], at[i], temp[i], ct[i], tt[i], wt[i]);
        avg_tt += tt[i];
        avg_wt += wt[i];
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("\nAverage Turnaround Time: %.2f\n", avg_tt / n);
    printf("Average Waiting Time: %.2f\n", avg_wt / n);
    
    printf("Gantt Chart\n");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0;i<n;i++)
	{
		printf("|\tP%d\t|",p[i]);
	}
	printf("\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("0\t\t");
	for(int i=0;i<n;i++)
	{
		printf("%d\t\t",ct[i]);
	}
	printf("\n");
	
    return 0;
}
