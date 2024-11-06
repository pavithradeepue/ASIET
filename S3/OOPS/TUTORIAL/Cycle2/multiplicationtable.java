/*Pavithra Deepu E
CSE AI 47
Program for printing the Multiplication Table.
TUTORIAL*/
import java.util.*;
class multiplicationtable
{
	public static void main(String args[])
	{
		Scanner S=new Scanner(System.in);
		System.out.println("enter the number :");
		int n= S.nextInt();
		System.out.println("enter the range:");
		int m=S.nextInt();
		System.out.println("the multiplication table:");
		for(int i=0;i<=m;i++)
		{	
			System.out.println(n+"x"+i+"="+n*i);
		}
		S.close();
	}
}
