#include <cmath>
#include <iostream>
#include "cordic-32bit.h"
#include "fast_sincosf.h"

#define PRECISION 64


using namespace std;

typedef double double2_t __attribute__ ((vector_size (2 * sizeof(double))));
double2_t double2_0 = {0, 0};

   // lookup table contains 64 values for sin(x), where 0 <= x < 2*pi
double lookup[PRECISION];

void init_table(){
	for(int i = 0; i < PRECISION; i++)
		lookup[i] = sin(i * M_PI * 2 / PRECISION);
}

void FastSinCos(double x, double *sin, double *cos)
{
	//Overflow of the int becomes a problem somewhere after x = 1e8
	double offset = x > 0 ? 0.5 : -0.5;
	int index = static_cast<int>(x * (PRECISION * 0.5 / M_PI) + offset);

	// distance from the point in lookup table
	double dt = x - (M_PI * 2 / PRECISION) * index;


	// index & 63 == index % 64
	int index1 = index & (PRECISION-1);
	int index2 = (index + (PRECISION/4)) & (PRECISION-1);

	// s is the closest value of sine from lookup table, c is cos
	double s = lookup[index1];
	double c = lookup[index2];

	double dt2 = dt * dt;
	double dt4 = dt2 * dt2;

	double second = 1 - dt2 * (1./6.);
	double first = 1 - dt2 * (1./2.);

	second += dt4 * (1./120.);
	first += dt4 * (1./24.);

	second *= dt;
	// {sin(x), cos(x)}
	*sin = s * first + c * second;
	*cos = c * first - s * second;
}

double FastSin(double x)
{
	//Overflow of the int becomes a problem somewhere after x = 1e8
	double offset = x > 0 ? 0.5 : -0.5;
	int index = static_cast<int>(x * (PRECISION * 0.5 / M_PI) + offset);

	// distance from the point in lookup table
	double dt = x - (M_PI * 2 / PRECISION) * index;

	// index & 63 == index % 64
	int index1 = index & (PRECISION-1);
	int index2 = (index + (PRECISION/4)) & (PRECISION-1);

	// s is the closest value of sine from lookup table, c is cos
	double2_t sc = {lookup[index1], lookup[index2]};

	double dt2 = dt * dt;
	double dt4 = dt2 * dt2;

	double2_t dt2_ = {dt2, dt2};
	double2_t dt4_ = {dt4, dt4};
	
	double2_t parts = {1, 1};

	double2_t mult1 = {1./2., 1./6.};
	parts -= dt2_ * mult1;

	double2_t mult2 = {1./24., 1./120.};
	parts += dt4_ * mult2;

	parts *= sc;

	return parts[0] + parts[1] * dt;

}


double FastCos(double x)
{
	//Overflow of the int becomes a problem somewhere after x = 1e8
	double offset = x > 0 ? 0.5 : -0.5;
	int index = static_cast<int>(x * (PRECISION * 0.5 / M_PI) + offset);

	// distance from the point in lookup table
	double dt = x - (M_PI * 2 / PRECISION) * index;

	// index & 63 == index % 64
	int index1 = index & (PRECISION-1);
	int index2 = (index + (PRECISION/4)) & (PRECISION-1);

	// s is the closest value of sine from lookup table, c is cos
	double s = lookup[index1];
	double c = lookup[index2];

	double dt2 = dt * dt;
	double dt4 = dt2 * dt2;

	double second = 1 - dt2 * (1./6.);
	double first = 1 - dt2 * (1./2.);

	second += dt4 * (1./120.);
	first += dt4 * (1./24.);// - dt4 * (dt2 * (1./720.));

	second *= dt;
	return c * first - s * second;

}

double cordic(double x){
	
        int sin, cos;       

        cordic(x * MUL, &sin, &cos);
	return (1/MUL) * sin;
}

