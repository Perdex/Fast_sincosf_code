#include <iostream>
#include <cstring>
#include "tester.h"

using namespace std;
void testRange(float from, float to, unsigned int batch, bool s, bool a){
	unsigned int f, t;
	memcpy(&f, &from, sizeof from);
	memcpy(&t, &to, sizeof to);

	cout << "\nTesting all " << t - f << " values between " 
		<< from << " and " << to << ":\n";

	if(s)
		testSpeed(f, t, batch);
	if(a)
		testAcc(f, t, batch);
}

int main(int argc, char **args){


	bool speed = false;
	bool acc = false;
	for(int i = 0; i < argc; i++){
		if(args[i][0] == 's')
			speed = true;
		if(args[i][0] == 'a')
			acc = true;
	}
	if(!(speed || acc))
		speed = acc = true;

	unsigned int batch = 10000000;
	testRange(0.01, 10, batch, speed, acc);
	testRange(-0.01, -10, batch, speed, acc);

	return 0;
}
