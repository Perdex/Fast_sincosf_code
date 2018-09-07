public class AccuracyTest{

	public static void test(float from, int n){

		float x = from;
		System.out.println("Testing accuracy:");
		System.out.print("Testing range [" + x + ", ");

		long start = System.nanoTime();

		int countEqual = 0, countNot = 0;
		float maxErr = 0f, maxRelErr = 0f;
		for(int i = 0; i < n; i++){
			float fast = FastSin.fastSin(x);
			float ref = (float)Math.sin(x);

			int equal = fast == ref ? 1 : 0;
			countEqual += equal;
			countNot += 1 - equal;

			float d = ref - fast;
			maxErr = Math.max(maxErr, Math.abs(d));
			maxRelErr = Math.max(maxRelErr, Math.abs(d/x));

			x = Math.nextUp(x);
		}
		long end = System.nanoTime();

		System.out.println(x + "]:");
		System.out.println("Correct  / incorrect: " + countEqual + " / " + countNot);
		System.out.println("Max error: " + maxErr);
		System.out.println("Max relative error: " + maxRelErr);
		System.out.println();

	}
}
