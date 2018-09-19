#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <ctime>
#include <cstring>
#include "fast_sincosf.h"
#include "colors.h"
using namespace std;

void test(double (*func)(double), double (*comp)(double), unsigned int, unsigned int, unsigned int);

double sinf_(double x){
	return sinf(x);
}

double cosf_(double x){
	return cosf(x);
}

double sincoss(double x){
	double2_t sincos = FastSinCos(x);
	return sincos[0];
}
double sincosc(double x){
	double2_t sincos = FastSinCos(x);
	return sincos[1];
}

void testAcc(unsigned int f, unsigned int t, unsigned int batch, bool testSin, bool testCos, bool testSinCos){

	if(testSin){
		cout << "Testing ";
		yellow("my sin");
		cout << "\n";
		test(FastSin, sin, f, t, batch);
	}
	if(testCos){
		cout << "Testing ";
		yellow("my cos");
		cout << "\n";
		test(FastCos, cos, f, t, batch);
	}

	if(testSin){
		cout << "Testing ";
		yellow("sinf");
		cout << "\n";
		test(sinf_, sin, f, t, batch);
	}
	
	if(testCos){
		cout << "Testing ";
		yellow("cosf");
		cout << "\n";
		test(cosf_, cos, f, t, batch);
	}
	if(testSinCos){

		cout << "Testing ";
		yellow("sin of my sincos");
		cout << "\n";
		test(sincoss, sin, f, t, batch);

		cout << "Testing ";
		yellow("cos of my sincos");
		cout << "\n";
		test(sincosc, cos, f, t, batch);
	}
}

void test(double (*func)(double), double (*comp)(double), unsigned int f, unsigned int t, unsigned int batch){
	cout << setprecision(3) << "Range [from, to]: ";
	green("correct");
	cout << " / ";
	red("incorrect");
	cout << "; max rel error, location" << endl;
	clock_t c_start = clock();

	unsigned int zeroes_ = 0, errors_ = 0;
	

	float maxerr = 0;
	float maxerrlocation = 0;
	for(unsigned int from = f; from < t; from += batch){
		unsigned int to = from + batch;
		unsigned int zeroes = 0, errors = 0;
		float rmaxerr = 0;
		float rmaxerrlocation = 0;
		
		init_table();
		
		
		for(unsigned int i = from; i < to; i++){
			float x;
			std::memcpy(&x, &i, sizeof x);
			float val = func(x);
			float ref = (float)comp((double)x);
			float err = abs(ref - val);
			float Rerr = abs(err / ref);
			
			if(err > maxerr){
				maxerr = err;
				maxerrlocation = x;
			}
			
			
			if(Rerr > rmaxerr){
				rmaxerr = Rerr;
				rmaxerrlocation = x;
			}
			
			if(err == 0){
				zeroes++;
			}else{
				errors++;
				if(err == INFINITY){
					cout << setprecision(20);
					cout << "Error is INF: i = " << i << "\tx = " << x << ",\tval = " << val << ",\terr = " << err << "\n";
					break;
				}
			}
			
		}
		
		float f_;
		float t_;
		std::memcpy(&f_, &from, sizeof f_);
		std::memcpy(&t_, &to, sizeof t_);
		cout << "Range [" << f_ << ", " << t_ << "]:\t";
		green(zeroes);
		cout << " / ";
		red(errors);
		cout << ";\t" << rmaxerr 
			<< "\t@ x = " << rmaxerrlocation << endl;

		zeroes_ += zeroes;
		errors_ += errors;
	}
	clock_t c_end = clock();
	auto time_used = 1000 * (c_end-c_start) / CLOCKS_PER_SEC;
	cout << "\nThere was \033[32m" << zeroes_ << "\033[0m correct values, \033[31m" << errors_
		<< "\033[0m incorrect ones.\nMax error was " << maxerr 
		<< ",\tfound at x = " << maxerrlocation
		<< ".\nThis took " << 0.001 * time_used << " s\n" << endl;
}
