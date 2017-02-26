#ifndef findAzimuth_h
#define findAzimuth_h

#include <cmath>
#include "Location.h"
#include "Location3D.h"

double calculateDistance(Location, Location);
double getQuadrant(Location, Location);
double calculateAzimuth(Location, Location);
void getIntervals(Location, double, double, int);

#endif
