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
	cout << "\nTesting all " << ntrue / 1000000 << " million values between " 
		<< from << " and " << toceilf << ":\n";

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
	// If no arguments given, test both
	if(!(speed || acc))
		speed = acc = true;

	unsigned int batch = 10000000;
	testRange(0.01, 10, batch, speed, acc);
	testRange(-0.01, -10, batch, speed, acc);

	return 0;
}
