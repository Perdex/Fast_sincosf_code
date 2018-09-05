
public class Tester{
	public static void main(String args[]){

		float from = 0.0001f;
		int n = 200000000;
		SpeedTest.test(from, n);
		AccuracyTest.test(from, n);
		
	}
}
