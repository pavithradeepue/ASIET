import java.util.Scanner;

class sumofnumbers {
    public static void main(String args[]) {
        int sum=0;
        int num, n;
        
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the number of elements:");
        n = s.nextInt();
        
        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            num = s.nextInt();
            {
            	sum=sum+num;
            }
        }
        
        System.out.println("The sum of numbers is: " + sum);
        s.close();
    }
}
