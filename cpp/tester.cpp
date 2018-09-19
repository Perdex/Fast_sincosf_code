#include <iostream>
#include <cstring>
#include <cmath>
#include "tester.h"

using namespace std;
void testRange(float from, float to, unsigned int batch, bool s, bool a){
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
		testSpeed(f, t, batch);
	if(a)
		testAcc(f, t, batch);
}

int main(int argc, char **args){

	// Parse arguments
	bool speed = false;
	bool acc = false;
	for(int i = 1; i < argc; i++){
		if(args[i][0] == 's')
			speed = true;
		if(args[i][0] == 'a')
			acc = true;
	}
	bool neither = false;
	// If no arguments given, test both
	if(!(speed || acc)){
		neither = true;
		speed = acc = true;
	}

	unsigned int batch = 10000000;
	// only run the small tests when no argument given
	if(neither){
		testRange(1e-10, 0.0015, batch * 10, false, acc);
		testRange(-1e-10, -0.0015, batch * 10, false, acc);
	}
	testRange(0.0015, 10, batch, speed, acc);
	testRange(-0.0015, -10, batch, speed, acc);

	return 0;
}
