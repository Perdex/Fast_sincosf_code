#include <cmath>
#include <iostream>
#include "fast_sincosf.h"

#define PRECISION 128


using namespace std;

   // lookup table contains 64 values for sin(x), where 0 <= x < 2*pi
double lookup[PRECISION];

void init_table(){
	for(int i = 0; i < PRECISION; i++)
		lookup[i] = sin(i * M_PI * 2 / PRECISION);
}

void FastSinCos(float x, float *sin, float *cos)
{
	//double x = fmod(x_, 2 * M_PI);
	//Overflow of the int becomes a problem somewhere 
	int index = static_cast<int>(x * (PRECISION * 0.5 / M_PI) + 0.5);

	// distance from the point in lookup table
	double dt = x - (M_PI * 2 / PRECISION) * index;
	#ifdef DEBUG
		cout << "\nx_ is\t" << x
			<< "\nx is\t" << x
			<< "\nind0 is\t" << x * (PRECISION * 0.5 / M_PI) + 0.5
			<< "\nind1 is\t" << index
			<< "\ndt is\t" << dt
			<< "\n";
	#endif
	// 0 <= index < 64
	// index & 63 == index % 64
	index &= (PRECISION-1);

	// s is the value of sine (floored) from lookup table, c is cos
	double s = lookup[index];
	double c = lookup[(index + (PRECISION/4)) & (PRECISION-1)];

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
	#ifdef DEBUG
		cout << "ind2 is\t" << index
			<< "\ns is\t" << s
			<< "\nc is\t" << c
			<< "\nfirst is\t" << first
			<< "\nsecond is\t" << second
			<< "\n";
	#endif

	// {sin(x), cos(x)}
	*sin = s * first + c * second;
	*cos = c * first - s * second;
}

float FastSin(float x)
{
	//double x = fmod(x_, 2 * M_PI);
	//Overflow of the int becomes a problem somewhere after x = 1e8
	float offset = x > 0 ? 0.5f : -0.5f;
	int index = static_cast<int>(x * (PRECISION * 0.5 / M_PI) + offset);

	// distance from the point in lookup table
	double dt = x - (M_PI * 2 / PRECISION) * index;

	// index & 63 == index % 64
	int index1 = index & (PRECISION-1);
	int index2 = index + (PRECISION/4);


	// s is the value of sine (floored) from lookup table, c is cos
	double s = lookup[index1];
	double c = lookup[index2 & (PRECISION-1)];

	double dt2 = dt * dt;
	double dt4 = dt2 * dt2;

	double second = 1 - dt2 * (1./6.);
	double first = 1 - dt2 * (1./2.);

	second += dt4 * (1./120.);
	first += dt4 * (1./24.);

	second *= dt;
	return s * first + c * second;
}


