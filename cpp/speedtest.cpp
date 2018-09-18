#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <x86intrin.h>
#include <ctime>
#include <chrono>
#include <cstring>
#include "fast_sincosf.h"

#define chronocast chrono::duration_cast<chrono::duration<double>>

using namespace std;
void testSpeed(unsigned int ff, unsigned int tt, unsigned int batch){

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
			init_table();
			auto chrono_t1 = chrono::high_resolution_clock::now();

			double sum = 0;

			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				sum += FastSin(x);
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;
			cout << cycles_per << " / std::sin: ";
				//<< "\nReal time (std::chrono): " << time_span.count() << " s"
		}
		
		{
			//cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();

			
			float sum = 0;
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				sum += sin(x);
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;
			cout << cycles_per << " / std::sinf: ";
		}
		{
			//cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();

			
			float sum = 0;
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				sum += sinf(x);
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;
			cout << cycles_per << "\n";
		}
	}
	cout << "(sum is " << summ << ")\n";

}
