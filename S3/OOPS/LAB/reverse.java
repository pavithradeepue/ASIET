/*Pavithra Deepu E
S3 CSAI
Roll No 47
Program to print reverse of a string.*/
import java.util.Scanner;
Class reverse 
{
    Public static void main(String[] args) 
    {
        String str, rev = “”;
        Scanner S1 = new Scanner(System.in);
        System.out.println(“Enter the string:”);
        Str = S1.nextLine();
        int length = str.length();

        for (int i = length – 1; i >= 0; i--) 
        {
            Reverse = reverse + str.charAt(i);
        }
        System.out.println(“The Reverse string is: “+rev);
        S1.close();
    }
}
