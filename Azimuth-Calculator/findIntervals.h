#ifndef findIntervals_h
#define findIntervals_h

#include <iostream>
using namespace std;

#include <cmath>
#include <cstdlib>
#include "Location.h"
#include "Location3D.h"

double getIncreaceEasting(int sizeOfInterval, double azimuth);
double getIncreaceNorthing(int sizeOfInterval, double azimuth);
void getIntervals(Location p1, double distance, double azimuth, int sizeOfInterval);

#endif
