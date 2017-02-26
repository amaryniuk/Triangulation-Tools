#ifndef DetermineStations_h
#define DetermineStations_h

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Location.h"
using namespace std;

const double pi_over_180 = 0.01745329;

// HORIZONTAL CHAINAGE
double getIncreaceEasting(double azimuth, int sizeOfInterval);
double getIncreaceNorthing(double azimuth, int sizeOfInterval);
double getIncreaceElevation(double azimuth, int sizeOfInterval);
Location nextStation_Horizontal(Location p1, double horizontal, double azimuth, int sizeOfInterval);

//SLOPE CHAINAGE
Location nextStation_Slope(Location p1, double slopeDistance, double slopeAngle, double azimuth, int sizeOfInterval);

#endif
