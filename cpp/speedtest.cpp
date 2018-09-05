#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <x86intrin.h>
#include <ctime>
#include <chrono>
#include <cstring>
#include "fast_sincosf.h"


using namespace std;
int main(int argc, char **args){
	
	//unsigned int from = 1000000000;
	//unsigned int to = 1100000000;
	unsigned int ff = 100000000;
	unsigned int tt = 1200000000;
	unsigned int batch = 200000000;

	for(unsigned int from = ff; from < tt; from += batch){

		unsigned int to = from + batch;
		unsigned int n = from - to;
		float f_;
		float t_;
		std::memcpy(&f_, &from, sizeof f_);
		std::memcpy(&t_, &to, sizeof t_);
		cout << "\nTesting range from " << f_ << " to " << t_ << "\n";

		{
			cout << "My method:\t";
			init_table();
			auto chrono_t1 = chrono::high_resolution_clock::now();
			clock_t c_start = clock();
			

			float sum = 0;

			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				//float sin, cos;
				//FastSinCos(*x, &sin, &cos);
				//sum += sin + cos;

				sum += FastSin(x);

				//if(i % 100000000 == 0)
				//	cout << "i: " << i/1000000 << " M\tx: " << *x << "\n";
				
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chrono::duration_cast<chrono::duration<double>>(chrono_t2 - chrono_t1);

			clock_t c_end = clock();
			double time_used = 0.001 * (1000 * (c_end-c_start) / CLOCKS_PER_SEC);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			cout << setprecision(3);
			cout << "Sum was " << sum << ", t:\t" << time_used << " s, \tcycles:\t" << cycles_per << "\n";
				//<< "\nProcessor time (std::clock):\t" << time_used << " s"
				//<< "\nReal time (std::chrono): " << time_span.count() << " s"
				//<< "\nCycles per calculation:\t" << cycles_per << endl;
		}
		
		{
			cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			clock_t c_start = clock();

			
			float sum = 0;
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				sum += sin(x);

				//if(i % 100000000 == 0)
				//	cout << "i: " << i/1000000 << " M\tx: " << *x << "\n";
				
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chrono::duration_cast<chrono::duration<double>>(chrono_t2 - chrono_t1);

			clock_t c_end = clock();
			double time_used = 0.001 * (1000 * (c_end-c_start) / CLOCKS_PER_SEC);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			cout << setprecision(3);
			cout << "Sum was " << sum << ", t:\t" << time_used << " s, \tcycles:\t" << cycles_per << "\n";
				//<< "\nProcessor time (std::clock):\t" << time_used << " s"
				//<< "\nReal time (std::chrono): " << time_span.count() << " s"
				//<< "\nCycles per calculation:\t" << cycles_per << endl;
		}
	}
	return 0;
}
