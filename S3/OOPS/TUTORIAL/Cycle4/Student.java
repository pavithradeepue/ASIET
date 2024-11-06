/*Pavithra Deepu E
S3 CSEAI 47
Program too create user defined package
TUTORIAL*/

package student; 

public class Student 
{

    String name;
    int age;

    public Student(String name, int age) 
    {
        this.name = name;
        this.age = age;
    }

    public void displayDetails() 
    {
        System.out.println("Student Name: " + name);
        System.out.println("Student Age: " + age);
    }
}

