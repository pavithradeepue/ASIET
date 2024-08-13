/*Pavithra Deepu E
S3 CSAI
Roll No:47
Program to perform linear search.*/
#include <stdio.h>
void main()
{
	int a[10],x,i,n;
	printf("Enter the number of elements:");
	scanf("%d",&n);
	printf("Enter the elements:  ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("Enter the search element:");
	scanf("%d",&x);
	for(i=0;i<n;i++)
		{
			if(a[i]==x)
			{
				printf("The search element is present at location %d\n",i+1);
				break;
			}
		}
	if(i==n)
	{
		printf("The element is not present.");
  }	
}
