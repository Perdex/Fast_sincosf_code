#include <iostream>
#include <cstring>
#include <cmath>
#include "tester.h"

using namespace std;
void testRange(float from, float to, unsigned int batch, bool s, bool a, bool sin, bool cos, bool sincos){
	unsigned int f, t;
	memcpy(&f, &from, sizeof from);
	memcpy(&t, &to, sizeof to);

	int ntrue = batch * ceil((float)(t-f)/batch);
	int toceil = f + ntrue;
	float toceilf;
	memcpy(&toceilf, &toceil, sizeof toceilf);

	if(s || a)
		cout << "\n\033[32mTesting all " << ntrue / 1000000 << " million values between " 
			<< from << " and " << toceilf << ":\n\033[0m\n";

	if(s)
		testSpeed(f, t, batch, sin, cos, sincos);
	if(a)
		testAcc(f, t, batch, sin, cos);
}

int main(int argc, char **args){

	// Parse arguments
	bool speed = false;
	bool acc = false;
	bool sin = false;
	bool cos = false;
	bool sincos = false;

	for(int i = 1; i < argc; i++){
		switch(args[i][0]){
			case 'p':
				speed = true;
				break;
			case 'a':
				acc = true;
				break;

			case 's':
				sin = true;
				break;
			case 'c':
				cos = true;
				break;
			case 'b':
				sincos = true;
				break;
		}
	}
	bool neither = false;
	// If no arguments given, test both
	if(!(speed || acc)){
		neither = true;
		speed = acc = true;
	}
	if(!(sin || cos || sincos))
		sin = cos = sincos = true;

	unsigned int batch = 10000000;
	// only run the small tests when no argument given
	if(neither){
		testRange(1e-10, 0.0015, batch * 10, false, acc, sin, cos, sincos);
		testRange(-1e-10, -0.0015, batch * 10, false, acc, sin, cos, sincos);
	}
	testRange(0.0015, 10, batch, speed, acc, sin, cos, sincos);
	testRange(-0.0015, -10, batch, speed, acc, sin, cos, sincos);

	return 0;
}
