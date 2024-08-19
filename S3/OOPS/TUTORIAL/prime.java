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
