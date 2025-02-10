#include <stdio.h>
void main()
{
	int i,n;
	int p[100],wt[100],at[100],bt[100],tt[100];
	float avgwt=0,avgtt=0;
	printf("Enter number of process:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter the process ID:");
		scanf("%d",&p[i]);
		/*printf("Enter arrival time:");
		scanf("%d",&at[i]);*/
		printf("Enter burst time:");
		scanf("%d",&bt[i]);
	}
	wt[0]=0;
	for(i=1;i<n;i++)
	{
		wt[i] = bt[i-1] + wt[i-1];
		avgwt += wt[i];
	}
	for(i=0;i<n;i++)
	{
		tt[i] = wt[i] + bt[i];
		avgtt += tt[i];
		
	}
	
	printf("Process Id\tBurst Time\tWaiting Time\tTurn Around Time\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\n",p[i],bt[i],wt[i],tt[i]);
	}
	printf("Average Waiting Time:%f\n",avgwt/n);
	printf("Average Turn Around Time:%f\n",avgtt/n);
	
	printf("\nGANT CHART\n");
	printf("----------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("|\tP%d\t|",p[i]);
	}
	printf("\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("0\t\t");
	for(i=0;i<n;i++)
	{
		printf("%d\t\t",tt[i]);
	}
	printf("\n");
	
	
}





























