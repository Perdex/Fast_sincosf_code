#include <iostream>
#include <cstring>
#include "tester.h"

using namespace std;
int main(int argc, char **args){
	
	float from = 0.001, to = 10;
	unsigned int f, t, batch = 10000000;
	memcpy(&f, &from, sizeof from);
	memcpy(&t, &to, sizeof to);

	cout << "Testing all " << t - f << " values between " << from << " and " << to << "\n\n";

	testSpeed(f, t, batch);
	testAcc(f, t, batch);
	return 0;
}
