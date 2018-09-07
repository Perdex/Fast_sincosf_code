
public class SpeedTest{

	public static void test(float from, int n, int batch){

		System.out.println("\nTesting speed, times are: my method / Math.sin / StrictMath.sin");
		float x_ = from;
		for(int f = 0; f < n; f += batch){
			float x = x_;
			System.out.printf("Testing range [%.3f, ", x);

			long start = System.nanoTime();

			float sum = 0;
			for(int i = 0; i < batch; i++){
				sum += FastSin.fastSin(x);
				x = Math.nextUp(x);
			}
			long end = System.nanoTime();

			System.out.printf("%.3f]: ", x);
			System.out.print((end - start) / 1000000 + " / ");

			x = x_;
			start = System.nanoTime();
			sum = 0;
			for(int i = 0; i < batch; i++){
				sum += Math.sin(x);
				x = Math.nextUp(x);
			}
			end = System.nanoTime();

			System.out.print((end - start) / 1000000 + " / ");

			x = x_;
			start = System.nanoTime();
			sum = 0;
			for(int i = 0; i < batch; i++){
				sum += StrictMath.sin(x);
				x = Math.nextUp(x);
			}
			end = System.nanoTime();
			x_ = x;

			System.out.println((end - start) / 1000000 + " ms");
		}
		System.out.println();
	}
}
