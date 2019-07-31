public class FastSinCos{

	static double lookup[] = new double[64];
	static{
		for(int i = 0; i < 64; i++)
			lookup[i] = Math.sin(i * Math.PI / 32);
	}
	static float fastSin(float x){
		float offset = x > 0 ? 0.5f : -0.5f;
		int index = (int)(x * (32 / Math.PI) + offset);

		// distance from the point in lookup table
		double dt = x - (Math.PI / 32) * index;

		// 0 <= index < 64
		// index & 63 == index % 64
		index &= 63;

		// s is the value of sine (floored) from lookup table, c is cos
		double s = lookup[index];
		double c = lookup[(index + 16) & (63)];

		// dt2 = dt^2/2 and so on, all with integration constants
		double dt2 = dt * dt * (1./2.);
		double dt3 = dt2 * (dt * (1./3.));
		double dt4 = dt3 * (dt * (1./4.));
		double dt5 = dt4 * (dt * (1./5.));
		double dt6 = dt5 * (dt * (1./6.));
		//double dt7 = dt6 * (dt * (1./7.));

		// the sums are same for sin and cos (Taylor):
		double first = 1 - dt2 + dt4 - dt6;
		double second = dt - dt3 + dt5;

		// {sin(x), cos(x)}
		return (float)(s * first + c * second);

	}
	static float fastCos(float x){
		float offset = x > 0 ? 0.5f : -0.5f;
		int index = (int)(x * (32 / Math.PI) + offset);

		// distance from the point in lookup table
		double dt = x - (Math.PI / 32) * index;

		// 0 <= index < 64
		// index & 63 == index % 64
		index &= 63;

		// s is the value of sine (floored) from lookup table, c is cos
		double s = lookup[index];
		double c = lookup[(index + 16) & (63)];

		// dt2 = dt^2/2 and so on, all with integration constants
		double dt2 = dt * dt * (1./2.);
		double dt3 = dt2 * (dt * (1./3.));
		double dt4 = dt3 * (dt * (1./4.));
		double dt5 = dt4 * (dt * (1./5.));
		double dt6 = dt5 * (dt * (1./6.));
		//double dt7 = dt6 * (dt * (1./7.));

		// the sums are same for sin and cos (Taylor):
		double first = 1 - dt2 + dt4 - dt6;
		double second = dt - dt3 + dt5;

		// {sin(x), cos(x)}
		return (float)(c * first - s * second);

	}
}

