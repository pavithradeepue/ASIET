import java.util.*;

class largestofn
{
	public static void main(String args[])
	{
	int large=0;
    int num, n;
        
    Scanner s1 = new Scanner(System.in);
    System.out.println("Enter the total elements:");
    n = s1.nextInt();
        
    System.out.println("Enter the elements:");
    for (int i = 0; i < n; i++) 
    {
    	num = s1.nextInt();
    	if (num > large)
    	{
    	large = num;
        }
    }
        
        System.out.println("The largest number is:" + large);
        s1.close();
    }
}

