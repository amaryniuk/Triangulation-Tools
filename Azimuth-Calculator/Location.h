#ifndef Location_h
#define Location_h

#include <iostream>
using namespace std;

class Location
{
public:
	Location();
	Location(double, double);

	void showLocation();
	double getEasting() { return easting; }
	double getNorthing() { return northing; }
	bool isEqual(Location p);

	Location operator-(Location p);
	Location operator=(Location p);

protected:
	double easting;
	double northing;
};

#endif
