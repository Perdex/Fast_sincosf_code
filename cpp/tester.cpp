#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <ctime>
#include "fast_sincosf.h"

using namespace std;
int main(int argc, char **args){
	
	cout << setprecision(3) << endl;
	
	unsigned int zeroes = 0, errors = 0;
	float maxerr = 0;
	float maxerrlocation = 0;
	float rmaxerr = 0;
	float rmaxerrlocation = 0;
	
	float shortmaxerr = 0;
	
    clock_t c_start = clock();

	//unsigned int step = 100;
	//for(unsigned int i = 0; i < i + step; i += step){
	for(unsigned int i = 1000000000; i < 1200000000; i++){
		float *x = reinterpret_cast<float*>(&i);
		float val = get<0>(FastSinCos(*x));
		float ref = sin(*x);
		float err = abs(ref - val);
		float Rerr = abs(err / ref);
		
		if(err > shortmaxerr){
			shortmaxerr = err;
			if(err > maxerr){
				maxerr = err;
				maxerrlocation = *x;
			}
		}
		
		if(Rerr > rmaxerr){
			rmaxerr = Rerr;
			rmaxerrlocation = *x;
		}
		
		zeroes += err == 0;
		errors += err != 0;
		
		if(i % 10000000 == 0){
			cout << "i: " << i/1000000 << " M\tx: " << *x 
			<< ", \tmax err: " << maxerr 
			<< ",\tshort max err: " << shortmaxerr
			<< ",\tmax rel err: " << rmaxerr  << "\n";
			shortmaxerr = 0;
		}
	}
	
    clock_t c_end = clock();
	auto time_used = (c_end-c_start) / CLOCKS_PER_SEC;
	
	cout << setprecision(8) << endl;
	cout << "Done!\nThere was " << zeroes << " correct values, " << errors
		<< " incorrect ones.\nMax error was " << maxerr 
		<< ", gotten at x = " << maxerrlocation
		<< "\nMax relative error was " << rmaxerr 
		<< ", gotten at x = " << rmaxerrlocation
		<< ".\nThis took " << time_used << " s" << endl;
	return 0;
}