import java.util.*;

class employee{
	int age;
	int phoneno;
	String name,address;
	double salary;
	int workyears;
	
	void printsal(){
		System.out.println("Salary:"+salary);
	}
}

class offficer extends employee{
	String special;
	
	void calculatesal(){
		double baseslary = 30000;
		if(special.equalsIgnorecase("Technical"))
		{
			slary = basesalary + 5000;
		}
		if else(special.equalsIgnorecase("Managerial")
		{
			slary = basesalary + 8000;
		}
		else
		{
			slary = basesalary;
		}
		salary += workyears + 1500;
	}
}


class print
{
	public static void main(String arags[])
	Scanner s = new Scanner(System.in);
	
	officer a = new officer();
	manager b = new manager();
	
	System.out.println("Enter the Officer's ");	
	
		
	
}
