#include <tuple>

// Calculates the sin and cosine quickly with accuracy of 10^-6 (typical error 10^-8)
// Uses a 6th order Taylor extension around the closest point in lookup table
//
// This could be made double-precision by increasing the order of approximation, but it would
// slow it down close to CPU FSINCOS call, and because of instruction-level parallelism it could
// even be slower. Double precision is rarely actually needed anyways, so this should be enough.
//
// returns a tuple {sin(x), cos(x)}
std::tuple<float, float> FastSinCos128(float x);
std::tuple<float, float> FastSinCos64(float x);
std::tuple<float, float> FastSinCos32(float x);