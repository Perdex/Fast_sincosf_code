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
	
	init_table();
	
    clock_t c_start = clock();
	
	unsigned int step = 1;
	//for(unsigned int i = 0; i < i + step; i += step){
	//for(unsigned int i = 1280000000; i < 2000000000; i += step){
	for(unsigned int i = 0; i < 1200000000; i+=step){
		float x;
		std::memcpy(&x, &i, sizeof x);
		float val = get<0>(FastSinCos(x));
		float ref = 0;//sin(*x);
		float err = abs(ref - val);
		float Rerr = abs(err / ref);
		
		if(err > shortmaxerr){
			shortmaxerr = err;
			if(err > maxerr){
				maxerr = err;
				maxerrlocation = x;
			}
		}
		
		if(Rerr > rmaxerr){
			rmaxerr = Rerr;
			rmaxerrlocation = x;
		}
		
		if(err == 0){
			zeroes++;
		}else{
			errors++;
			//cout << "Error: i = " << i << "\tx = " << *x << ",\tval = " << val << ",\terr = " << err << "\n";
			if(err == INFINITY){
				cout << setprecision(20);
				cout << "Error: i = " << i << "\tx = " << x << ",\tval = " << val << ",\terr = " << err << "\n";
				break;
			}
		}
		
		if(i % 100000000 == 0){
			cout << "i: " << i/1000000 << " M\tx: " << x 
			<< ", \tmax err: " << maxerr 
			<< ",\tshort max err: " << shortmaxerr
			<< ",\tmax rel err: " << rmaxerr  << "\n";
			shortmaxerr = 0;
		}
	}
	
    clock_t c_end = clock();
	auto time_used = 1000 * (c_end-c_start) / CLOCKS_PER_SEC;
	
	cout << setprecision(8) << endl;
	cout << "Done!\nThere was " << zeroes << " correct values, " << errors
		<< " incorrect ones.\nMax error was " << maxerr 
		<< ",\tfound at x = " << maxerrlocation
		<< "\nMax rel error was " << rmaxerr 
		<< ",\tfound at x = " << rmaxerrlocation
		<< ".\nThis took " << 0.001 * time_used << " s" << endl;
	return 0;
}
