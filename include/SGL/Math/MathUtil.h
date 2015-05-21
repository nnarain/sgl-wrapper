
#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>

// PI
#define PI              3.14159f
// convert degrees to radians
#define DEG_TO_RAD(deg) ((deg) * (PI/180.0f))

// sin in degrees
#define sinDeg(deg) sin(DEG_TO_RAD((deg)))
// cos in degrees
#define cosDeg(deg) cos(DEG_TO_RAD((deg)))
// tan in degrees
#define tanDeg(deg) tan(DEG_TO_RAD((deg)))

#endif
