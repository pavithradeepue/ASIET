//program to print sum of two numbers

import java.util.*;

class sumavg
{
    public static void main(String args[])
        {

            Scanner S1= new Scanner(System.in);
            System.out.println("Enter Three Numbers:");
            int a=S1.nextInt();
            int b=S1.nextInt(); 
            int c=S1.nextInt();
            int sum=a+b+c;
            int avg = sum/2;
            System.out.println ("The sum of is:" +sum);
            System.out.println("The average of the numbers is "+avg);
            S1.close();
        }

}

    

