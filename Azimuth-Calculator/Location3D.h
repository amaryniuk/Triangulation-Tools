#ifndef Location3D_h
#define Location3D_h

#include <iostream>
#include "Location.h"
using namespace std;



class Location3D : public Location
{
public:
	Location3D();
	Location3D(double, double, double);
//	~Location();

	void showLocation();
	double getElevation() { return elevation; }
	bool isEqual(Location3D p);

private:
	double elevation;

};

#endif