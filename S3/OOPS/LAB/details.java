import java.util.*;
class details
{
    public static void main(String args[])
    {
        Scanner S1 = new Scanner(System.in);
        int roll;
        String name,cls;
        System.out.println("Enter your Name:");
        name = S1.nextLine(); 
        System.out.println("Enter your Class:");
        cls = S1.nextLine();
        System.out.println("Enter your Roll No:");
        roll = S1.nextInt();

        System.out.println("Your name is: "+name);

        System.out.println("Class is: "+cls);

        System.out.println("Roll No is: "+roll);
        S1.close();
    }
}