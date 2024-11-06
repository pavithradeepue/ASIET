/*Pavithra Deepu E
CSE AI 47
Program for check whether a given number is prime or not.
TUTORIAL*/
import java.util.*;
public class primeornot 
{
    public static void main(String args[])
    {
        Scanner S=new Scanner(System.in);
        int count=0;
        System.out.println("enter the number");
         int n=S.nextInt();
         for(int i=1;i<=n;i++)
         {
            if(n%i==0)
            {
                count++;

            
            }
            }
                if(count==2)
                {
                    System.out.println(n+"is a prime number");
                }
            
                count=0;
        
            
         
         S.close();


    }

}
