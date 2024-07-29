import java.util.*;

class sumthree
{
    public static void main(String args[])

    {
        Scanner S1= new Scanner(System.in);
        System.out.println("Enter Three Numbers:");
        float a=S1.nextFloat();
        float b=S1.nextFloat();
        float c=S1.nextFloat();
        float sum=a+b+c;
        System.out.println("The sum is "+sum); 
        S1.close();
    }
}