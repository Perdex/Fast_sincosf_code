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
int testSpeed(unsigned int ff, unsigned int tt, unsigned int batch){
	
	float summ = 0;

	cout << setprecision(2);
	for(unsigned int from = ff; from < tt; from += batch){

		unsigned int to = from + batch;
		unsigned int n = batch;
		float f_;
		float t_;
		std::memcpy(&f_, &from, sizeof f_);
		std::memcpy(&t_, &to, sizeof t_);
		cout << "Cycles in [" << f_ << ", " << t_ << "]:\t";

		{
			//cout << "My method:\t";
			init_table();
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();
			

			float sum[4] = {0, 0, 0, 0};

			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i_ = from; i_ < to; i_+=4){
				for(unsigned int i = i_; i < i_ + 4; i++){
					float x;
					std::memcpy(&x, &i, sizeof x);
					//float sin, cos;
					//FastSinCos(*x, &sin, &cos);
					//sum += sin + cos;

					sum[i-i_] += FastSin(x);

					//if(i % 100000000 == 0)
					//	cout << "i: " << i/1000000 << " M\tx: " << *x << "\n";
				}
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chrono::duration_cast<chrono::duration<double>>(chrono_t2 - chrono_t1);

			//clock_t c_end = clock();
			//double time_used = 0.001 * (1000 * (c_end-c_start) / CLOCKS_PER_SEC);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			

			summ += sum[0] + sum[1] + sum[2] + sum[3];
			//cout << "Sum was " << summ << ", t:\t" 
			//	<< time_used << " s, \tcycles:\t" << cycles_per << "\n";
			cout << cycles_per << " / ";
				//<< "\nProcessor time (std::clock):\t" << time_used << " s"
				//<< "\nReal time (std::chrono): " << time_span.count() << " s"
				//<< "\nCycles per calculation:\t" << cycles_per << endl;
		}
		
		{
			//cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();

			
			float sum[4] = {0, 0, 0, 0};
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i_ = from; i_ < to; i_+=4)
				for(unsigned int i = i_; i < i_ + 4; i++){
					float x;
					std::memcpy(&x, &i, sizeof x);
					sum[i-i_] += sin(x);

					//if(i % 100000000 == 0)
					//	cout << "i: " << i/1000000 << " M\tx: " << *x << "\n";
					
				}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chrono::duration_cast<chrono::duration<double>>(chrono_t2 - chrono_t1);

			//clock_t c_end = clock();
			//double time_used = 0.001 * (1000 * (c_end-c_start) / CLOCKS_PER_SEC);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum[0] + sum[1] + sum[2] + sum[3];
			//cout << "Sum was " << summ << ", t:\t" 
			//	<< time_used << " s, \tcycles:\t" << cycles_per << "\n";
			cout << cycles_per << "\n";
				//<< "\nProcessor time (std::clock):\t" << time_used << " s"
				//<< "\nReal time (std::chrono): " << time_span.count() << " s"
				//<< "\nCycles per calculation:\t" << cycles_per << endl;
		}
	}
	cout << "(sum is " << summ << ")\n";
	return 0;
}
