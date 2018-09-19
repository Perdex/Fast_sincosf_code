#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <x86intrin.h>
#include <ctime>
#include <chrono>
#include <cstring>
#include "colors.h"
#include "fast_sincosf.h"

#define chronocast chrono::duration_cast<chrono::duration<double>>


using namespace std;
void testSpeed(unsigned int ff, unsigned int tt, unsigned int batch, bool testSin, bool testCos, bool testSinCos){

	cout << "Values are cycles for ";
	if(testSin){
		green("my sin");
		cout << ", ";
		yellow("std::sin");
		cout << ", ";
		blue("std::sinf");
	 	cout << "; ";
	}
	if(testCos){
		green("my cos");
		cout << ", ";
		yellow("std::cos");
		cout << ", ";
		blue("std::cosf");
	}
	if(testSinCos){
		cout << "; ";
		green("my sincos");
		cout << ", ";
		yellow("std::sincosf");
	}
	cout << ":\n";

	float summ = 0;

	cout << setprecision(3);
	for(unsigned int from = ff; from < tt; from += batch){

		unsigned int to = from + batch;
		unsigned int n = batch;
		float f_;
		float t_;
		std::memcpy(&f_, &from, sizeof f_);
		std::memcpy(&t_, &to, sizeof t_);
		cout << "Cycles in [" << f_ << ", " << t_ << "]:   ";

		if(testSin){
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
			cout << "\t";
			green(cycles_per);
			cout << ", ";
				//<< "\nReal time (std::chrono): " << time_span.count() << " s"
		}
		
		if(testSin){
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
			yellow(cycles_per);
			cout << ", ";
		}
		if(testSin){
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

			blue(cycles_per);
			cout << "; ";
		}
		/********************************
		* COS
		********************************/
		if(testCos){
			init_table();
			auto chrono_t1 = chrono::high_resolution_clock::now();

			double sum = 0;

			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				sum += FastCos(x);
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;
			cout << "\t";
			green(cycles_per);
			cout << ", ";
				//<< "\nReal time (std::chrono): " << time_span.count() << " s"
		}
		
		if(testCos){
			//cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();

			
			float sum = 0;
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				sum += cos(x);
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;
			yellow(cycles_per);
			cout << ", ";
		}
		if(testCos){
			//cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();

			
			float sum = 0;
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				sum += cosf(x);
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;

			blue(cycles_per);
			cout << "; ";
		}
		if(testSinCos){
			//cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();

			
			float sum = 0;
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				double2_t sincos = FastSinCos(x);
				sum += sincos[0];
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;

			cout << "\t";
			green(cycles_per);
			cout << ", ";
		}
		if(testSinCos){
			//cout << "std::sin:\t";
			auto chrono_t1 = chrono::high_resolution_clock::now();
			//clock_t c_start = clock();

			
			float sum = 0;
			unsigned long long cycles_start = __rdtsc();
			for(unsigned int i = from; i < to; i++){
				float x;
				std::memcpy(&x, &i, sizeof x);
				float sin, cos;
				sincosf(x, &sin, &cos);
				sum += sin;
			}
			unsigned long long cycles_end = __rdtsc();
			
			auto chrono_t2 = chrono::high_resolution_clock::now();
			auto time_span = chronocast(chrono_t2 - chrono_t1);

			double cycles_per = 0.001 * (1000 * (cycles_end - cycles_start) / n);
			
			summ += sum;

			yellow(cycles_per);
			cout << "; ";
		}
		cout << "\n";
	}
	cout << "(sum is " << summ << ")\n";

}
