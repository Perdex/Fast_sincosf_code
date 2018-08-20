#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <ctime>
#include <chrono>
#include "fast_sincosf.h"


using namespace std;
int main(int argc, char **args){
	
	
	unsigned int n = 1200000000;
	{
		cout << "Testing my method:\n";
		init_table();
		auto chrono_t1 = chrono::high_resolution_clock::now();
		clock_t c_start = clock();
		
		double sum = 0;
		//for(unsigned int i = 0; i < i + step; i += step){
		//for(unsigned int i = 1280000000; i < 2000000000; i += step){
		for(unsigned int i = 0; i < n; i++){
			float *x = reinterpret_cast<float*>(&i);
			
			sum += get<0>(FastSinCos(*x));

			if(i % 100000000 == 0)
				cout << "i: " << i/1000000 << " M\tx: " << *x << "\n";
			
		}
		
		auto chrono_t2 = chrono::high_resolution_clock::now();
		auto time_span = chrono::duration_cast<chrono::duration<double>>(chrono_t2 - chrono_t1);

		clock_t c_end = clock();
		double time_used = 0.001 * (1000 * (c_end-c_start) / CLOCKS_PER_SEC);
		double cycles_per = time_used * 3.2e9 / n;
		
		cout << setprecision(8) << endl;
		cout << "Done!\nSum was " << sum 
			<< "\nProcessor time (std::clock): " << time_used << " s"
			<< "\nReal time (std::chrono): " << time_span.count() << " s"
			<< "\nCycles per calculation: " << cycles_per << endl;
	}
	
	{
		cout << "\n\n\nTesting std::sin:\n";
		auto chrono_t1 = chrono::high_resolution_clock::now();
		clock_t c_start = clock();
		
		double sum = 0;
		//for(unsigned int i = 0; i < i + step; i += step){
		//for(unsigned int i = 1280000000; i < 2000000000; i += step){
		for(unsigned int i = 0; i < n; i++){
			float *x = reinterpret_cast<float*>(&i);
			
			sum += sin(*x);

			if(i % 100000000 == 0)
				cout << "i: " << i/1000000 << " M\tx: " << *x << "\n";
			
		}
		
		auto chrono_t2 = chrono::high_resolution_clock::now();
		auto time_span = chrono::duration_cast<chrono::duration<double>>(chrono_t2 - chrono_t1);

		clock_t c_end = clock();
		double time_used = 0.001 * (1000 * (c_end-c_start) / CLOCKS_PER_SEC);
		double cycles_per = time_used * 3.2e9 / n;
		
		cout << setprecision(8) << endl;
		cout << "Done!\nSum was " << sum 
			<< "\nProcessor time (std::clock): " << time_used << " s"
			<< "\nReal time (std::chrono): " << time_span.count() << " s"
			<< "\nCycles per calculation: " << cycles_per << endl;
	}
	return 0;
}