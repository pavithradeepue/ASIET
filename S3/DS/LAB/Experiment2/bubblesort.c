/*Pavithra Deepu E
S3 CSAI
Roll No:47
Program to perform bubble sort.*/
#include <stdio.h>
void main()
{
	int a[10],x,i,j,temp,n;
	printf("Enter the number of elements:");
	scanf("%d",&n);
	printf("Enter the elements:  ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
			temp = a[j];
			a[j] = a[j+1];
			a[j+1]=temp;
			}
		}
	}
	printf("The sorted array is:");
	for(i=0;i<n;i++)
	{
		printf("%d\t\n",a[i]);
	}
}
