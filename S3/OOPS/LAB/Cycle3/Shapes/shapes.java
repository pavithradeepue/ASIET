/* Pavithra Deepu E 
  S3 CseAI 47*/
import java.util.*;

abstract class Shape {
    void numberOfSides() {
    }
}

class Rectangle extends Shape {
    void numberOfSides() {
        System.out.println("The number of sides of a Rectangle is 4");
    }
}

class Triangle extends Shape {
    void numberOfSides() {
        System.out.println("The number of sides of a Triangle is 3");
    }
}

class Hexagon extends Shape {
    void numberOfSides() {
        System.out.println("The number of sides of a Hexagon is 6");
    }
}

class Main {
	public static void main(String[] args) 
	{
        Scanner S1 = new Scanner(System.in);

        Rectangle r = new Rectangle();
        Triangle t = new Triangle();
        Hexagon h = new Hexagon();
        
        r.numberOfSides();
        t.numberOfSides();
        h.numberOfSides();
        S1.close();
	}
}
