import java.lang.*;
import java.util.*;
class root
{
    public static void main (String args[])
    {
        int x,y;
        Scanner S1=new Scanner(System.in);
        System.out.println("Enter the value of x:");
        x=S1.nextInt();
        System.out.println( "Enter the value of y:");
        y=S1.nextInt();
        double sqrt=Math.sqrt(x);
        double power=Math.pow(x,y);
        System.out.println("The root is: "+sqrt); 
        System.out.println("The power is: "+power);
        S1.close();
    }
}