import java.util.*;
class arraysum
{
	public static void main(String args[])
	{
		int sum =0;
		int num[]=new int[50];
		Scanner S1=new Scanner (System.in);
		System.out.println("Enter the number of array elements:");
		int length=S1.nextInt();
		System.out.println("Enter the array elements:");
		for (int i=0;i<length;i++)
		{
			num[i]=S1.nextInt();
		}
		for (int i=0;i<length;i++)
		{
			sum=sum+num[i];
		}
		System.out.println("The sum of the matrix is: " +sum);
		S1.close();
		
	}
}
