
public class Tester{
	public static void main(String args[]){

		float from = 0.001f;
		int n = 100000000;
		SpeedTest.test(from, n);
		AccuracyTest.test(from, n);
		
	}
}
