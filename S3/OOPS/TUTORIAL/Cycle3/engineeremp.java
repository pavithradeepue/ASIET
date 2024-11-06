/*Pavithra Deepu E
S3 CSE AI 47
Program to display engineer salary.
TUTORIAL*/

import java.util.*;

class Employee 
{
    int salary;

    void display() 
    {
        System.out.println("Name of the class is Employee");
    }

    void calcSalary() 
    {
        System.out.println("Salary of the Employee is: " + salary);
    }
}

class Engineer extends Employee 
{ }

class engineeremp 
{
    public static void main(String[] args) 
    {
        Scanner s1 = new Scanner(System.in);
        Employee a = new Employee();
        Engineer b = new Engineer();

        System.out.println("Enter the salary of the employee:");
        a.salary = s1.nextInt();
        a.display();
        a.calcSalary();

        System.out.println("Enter the salary of the Engineer:");
        b.salary = s1.nextInt();
        b.display();
        b.calcSalary();

        s1.close();
    }
}
