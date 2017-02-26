#ifndef findAzimuth_h
#define findAzimuth_h

#include <cmath>
#include "Location.h"

int getQuadrant(Location, Location);
double calcHorizontal(Location, Location);
double calcAzimuth(Location, Location);
double calcSlope(Location, Location);
double calcElevation(Location, Location);
bool slopeIsNegative(double, double);

#endif
