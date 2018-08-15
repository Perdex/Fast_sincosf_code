#include <cmath>
#include "fast_sincosf.h"

using namespace std;

// Calculates the sin and cosine quickly with accuracy of 10^-6 (typical error 10^-8)
// Uses a 6th order Taylor extension around the closest point in lookup table
//
// This could be made double-precision by increasing the order of approximation, but it would
// slow it down close to CPU FSINCOS call, and because of instruction-level parallelism it could
// even be slower. Double precision is rarely actually needed anyways, so this should be enough.
//
// returns a tuple {sin(x), cos(x)}
tuple<float, float> FastSinCos(float x)
{
   // lookup table contains 64 values for sin(x), where 0 <= x < 2*pi
   static const double lookup[64] = {
      0, 0.098017140329560603629,
      0.19509032201612824808, 0.29028467725446233105,
      0.38268343236508978178, 0.47139673682599764204,
      0.55557023301960217765, 0.63439328416364548779,
      0.70710678118654746172, 0.77301045336273699338,
      0.83146961230254523567, 0.88192126434835493853,
      0.92387953251128673848, 0.9569403357322089354,
      0.98078528040323043058, 0.99518472667219681771,
      1, 0.99518472667219692873,
      0.98078528040323043058, 0.9569403357322089354,
      0.92387953251128673848, 0.88192126434835504956,
      0.83146961230254545772, 0.7730104533627371044,
      0.70710678118654757274, 0.63439328416364548779,
      0.55557023301960217765, 0.47139673682599786408,
      0.3826834323650898928, 0.29028467725446238656,
      0.19509032201612860891, 0.098017140329560825673,
      1.2246063538223772582e-16, -0.098017140329560589751,
      -0.19509032201612835911, -0.29028467725446210901,
      -0.38268343236508967076, -0.47139673682599764204,
      -0.5555702330196019556, -0.63439328416364526575,
      -0.70710678118654746172, -0.77301045336273666031,
      -0.83146961230254523567, -0.88192126434835493853,
      -0.92387953251128651644, -0.95694033573220882438,
      -0.98078528040323031956, -0.99518472667219692873,
      -1, -0.99518472667219692873,
      -0.98078528040323043058, -0.9569403357322089354,
      -0.92387953251128662746, -0.88192126434835504956,
      -0.83146961230254545772, -0.77301045336273688235,
      -0.70710678118654768376, -0.63439328416364593188,
      -0.55557023301960217765, -0.4713967368259979196,
      -0.3826834323650903924, -0.29028467725446249759,
      -0.19509032201612871993, -0.098017140329560506484
   };

   int index = static_cast<int>(x * (32. / M_PI) + 0.5);

   // distance from the point in lookup table
   double dt = x - (M_PI / 32.) * index;

   // 0 <= index < 64
   // index & 63 == index % 64
   index += 64;
   index &= 63;

   // s is the value of sine (floored) from lookup table, c is cos
   double s = lookup[index];
   double c = lookup[(index + 16) & 63];

   // dt2 = dt^2/2 and so on, all with integration constants
   double dt2 = dt * dt * (1./2.);
   double dt3 = dt2 * (dt * (1./3.));
   double dt4 = dt3 * (dt * (1./4.));
   double dt5 = dt4 * (dt * (1./5.));
   double dt6 = dt5 * (dt * (1./6.));
   double dt7 = dt6 * (dt * (1./7.));

   // the sums are same for sin and cos (Taylor):
   double first = 1 - dt2 + dt4;
   double second = dt - dt3 + dt5;

   // {sin(x), cos(x)}
   return make_tuple(static_cast<float>(s * first + c * second),
                     static_cast<float>(c * first - s * second));
}


