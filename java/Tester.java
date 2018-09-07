
public class Tester{
	public static void main(String args[]){

		float from = 0.001f;
		int n = 110000000;
		int batch = 10000000;
		SpeedTest.test(from, n, batch);
		AccuracyTest.test(from, n);

		from = -9.1f;

		SpeedTest.test(from, n, batch);
		AccuracyTest.test(from, n);
		
	}
}
