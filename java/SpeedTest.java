
public class SpeedTest{

	public static void test(float from, int n){

		float x = from;
		System.out.println("Testing speed from " + x + " for " + n + " values");

		long start = System.nanoTime();

		float sum = 0;
		for(int i = 0; i < n; i++){
			sum += FastSin.fastSin(x);
			x = Math.nextUp(x);
		}
		long end = System.nanoTime();

		System.out.println("Final x was " + x);
		System.out.println("My method took " + (end - start) / 1000000 + " ms");

		start = System.nanoTime();
		sum = 0;
		for(int i = 0; i < n; i++){
			sum += Math.sin(x);
			x = Math.nextUp(x);
		}
		end = System.nanoTime();

		System.out.println("Math.sin took " + (end - start) / 1000000 + " ms");
		System.out.println();
	}
}
