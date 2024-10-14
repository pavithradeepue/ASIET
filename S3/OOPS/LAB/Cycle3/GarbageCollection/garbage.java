/*Pavithra Deepu E
S3 CSEAI
47*/
import java.util.*;
class test
{
	protected void finalize()
	{
		System.out.println("Object is garbage collected.");
	}
	
	public static void main(String args[])
	{
		Scanner S = new Scanner(System.in);
		test S1 = new test();
		test S2 = new test();

		S1 = null;
		S2 = null;
		S.close();
		System.gc();		
	}
}
