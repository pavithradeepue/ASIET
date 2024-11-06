import student.Student;

public class MainClass 
{
    public static void main(String[] args) 
  {
        Student student1 = new Student("Alice", 20);
        student1.displayDetails();

        Student student2 = new Student("Bob", 22);
        student2.displayDetails();
    }
}
