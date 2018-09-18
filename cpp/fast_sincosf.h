#include <tuple>

// Calculates the sin and cosine quickly with accuracy of 10^-6 (typical error 10^-8)
// Uses a 6th order Taylor extension around the closest point in lookup table
//
// This could be made double-precision by increasing the order of approximation, but it would
// slow it down close to CPU FSINCOS call, and because of instruction-level parallelism it could
// even be slower. Double precision is rarely actually needed anyways, so this should be enough.
//
// If x goes over 180 000 000, the method might return inf due to integer overflow
//
// returns a tuple {sin(x), cos(x)}
void init_table();
void FastSinCos(float x, float *sin, float *cos);
double FastSin(double x);
double FastCos(double x);
double cordic(double x);
