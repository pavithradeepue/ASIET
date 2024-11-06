/* Pavithra Deepu E
S3 CSE-AI 47
Write a file handling program in Java with reader/writer*/

import java.io.*;
import java.util.*;

public class filehandling 
{
    static void readfile(){
        FileInputStream fin = null;

        try{

            fin = new FileInputStream("a.txt");
            int getsize=fin.available();
            System.out.println("file size is "+getsize);
            int i=0;
            while(i<getsize){
                System.out.println(fin.read());
                i++;
            }

        }
        catch(Exception e){
            System.out.println("error");
        }
        finally 
        {
            try 
            {
                if (fin != null)
                 {
                    fin.close();
                }
            } catch (IOException e) 
            {
                System.out.println("Error closing file:" + e.getMessage());
            }
        }
    }

    static void writefile(){

        Scanner s=new Scanner(System.in);
        FileOutputStream fos = null;

        try
        {

            fos = new FileOutputStream("a.txt");
            String str="";
            System.out.println("Enter the File Input:");
            str=s.nextLine();
            fos.write(str.getBytes());

        }
        catch(Exception e)
        {
            System.out.println("error"+e);
        }
        finally 
        {
            try 
            {
                if (fos != null) 
                {
                    fos.close();
                }
            } catch (IOException ex) 
            {
                System.out.println("Error closing file:" + ex.getMessage());
            }
        }
    }

    public static void main(String args[]) 
    {

        int k=0;
        Scanner s = new Scanner(System.in);

        while (k<2) {

            System.out.println("MENU");
            System.out.println("1. WRITE");
            System.out.println("2.READ");
            System.out.println("3.EXIT");
            k=s.nextInt();

            if (k==1) {
                writefile();
            }
            else if (k==2) {
                readfile();
            }
        }
    }
}
