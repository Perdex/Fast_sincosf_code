#include <iostream>

#define PRECISION 64
#define M_PI 3.1415926757
   // lookup table contains 64 values for sin(x), where 0 <= x < 2*pi
double lookup[PRECISION];
typedef double double2_t __attribute__ ((vector_size (2 * sizeof(double))));


double2_t FastSin(double x)
{
	//Overflow of the int becomes a problem somewhere after x = 1e8
	double offset = x > 0 ? 0.5 : -0.5;
	int index = static_cast<int>(x * (PRECISION * 0.5 / M_PI) + offset);

	// distance from the point in lookup table
	double dt = x - (M_PI * 2 / PRECISION) * index;
	double2_t dt_ = {dt, dt};

	// index & 63 == index % 64
	int index1 = index & (PRECISION-1);
	int index2 = (index + (PRECISION/4)) & (PRECISION-1);

	// s is the closest value of sine from lookup table, c is cos
	double2_t sc = {lookup[index1], lookup[index2]};

	double2_t dt2_ = dt_ * dt_;
	double2_t dt4_ = dt2_ * dt2_;
	
	double2_t parts = {1, 1};
	double2_t mult1 = {1./2., 1./6.};
	parts -= dt2_ * mult1;

	double2_t mult2 = {1./24., 1./120.};
	parts += dt4_ * mult2;

	parts *= sc;

	return parts[0] + parts[1] * dt;

}

int main(int argc, char **args){
	
	double ans = 0;
	for(double f = 0; f < 1; f += 0.001) ans += FastSin(f)[0];

	std::cout << ans << std::endl;
	return 0;
}
