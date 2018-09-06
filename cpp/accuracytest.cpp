#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <ctime>
#include <cstring>
#include "fast_sincosf.h"

using namespace std;
int testAcc(unsigned int f, unsigned int t, unsigned int batch){
	
	cout << endl << setprecision(2) << "Range [from, to]: correct/incorrect; max rel error, location" << endl;
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
			float val = FastSin(x);
			float ref = sin(x);
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
		
		//cout << setprecision(8) << endl;
		/*cout << "There was " << zeroes << " correct values, " << errors
			<< " incorrect ones.\nMax error was " << maxerr 
			<< ",\tfound at x = " << maxerrlocation
			<< "\nMax rel error was " << rmaxerr 
			<< ",\tfound at x = " << rmaxerrlocation
			<< ".\nThis took " << 0.001 * time_used << " s" << endl;
*/
		float f_;
		float t_;
		std::memcpy(&f_, &from, sizeof f_);
		std::memcpy(&t_, &to, sizeof t_);
		cout << "Range [" << f_ << ", " << t_ << "]:\t"
			<< zeroes << " / " << errors
			<< ";\t" << rmaxerr 
			<< "\t@ x = " << rmaxerrlocation << endl;

		zeroes_ += zeroes;
		errors_ += errors;
	}
	clock_t c_end = clock();
	auto time_used = 1000 * (c_end-c_start) / CLOCKS_PER_SEC;
	cout << "\nThere was " << zeroes_ << " correct values, " << errors_
		<< " incorrect ones.\nMax error was " << maxerr 
		<< ",\tfound at x = " << maxerrlocation
		<< ".\nThis took " << 0.001 * time_used << " s" << endl;
	return 0;
}
