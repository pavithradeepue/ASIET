#include <stdio.h>
void main()
{
    int i,j,n,temp;
    int p[100],wt[100],bt[100],tt[100],pr[100];
    int current_time;
    float avgtt=0,avgwt=0;

    printf("Enter the number of processes:");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter process Id:");
        scanf("%d",&p[i]);
        printf("Enter burst time:");
        scanf("%d",&bt[i]);
        printf("Enter priority(Lower number = higher priority):");
        scanf("%d",&pr[i]);
    }

    for(i = 0; i < n-1; i++){
        for(j = 0; j < n-i-1; j++){
            if(pr[j] > pr[j+1]) { 

                temp = pr[j];
                pr[j] = pr[j+1];
                pr[j+1] = temp;
                
                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;
                
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    wt[0]=0;
    avgwt=0;
    for(i=1;i<n;i++)
    {
        wt[i]=bt[i-1] + wt[i-1];
        avgwt +=wt[i];
    }
    avgtt=0;
    for(i=0;i<n;i++){
        tt[i] = wt[i]+bt[i];
        avgtt += tt[i];
    }

    printf("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurn Around Time\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i],bt[i],pr[i],wt[i],tt[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avgwt/n);
    printf("Average Turn Around Time: %.2f\n", avgtt/n);

    printf("GANT CHART \n");
    printf("---------------------------------------------------------------------------------------- \n");
    for (i = 0; i < n; i++) {
    	printf("|	%d	",p[i]);
    	printf("|");	
    }
    printf("\n");
    printf("---------------------------------------------------------------------------------------- \n");
    for (i = 0; i < n; i++) {
    	printf("%d		",wt[i]);
    }
}
