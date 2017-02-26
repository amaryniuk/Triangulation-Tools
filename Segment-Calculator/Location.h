// Location.h: interface for the Location class.
#if !defined(AFX_LOCATION_H__2CC0FD2D_6689_11D6_A105_0050DA102704__INCLUDED_)
#define AFX_LOCATION_H__2CC0FD2D_6689_11D6_A105_0050DA102704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
using namespace std;

class Location
{
public:
	Location();
//	Location(double, double);			// ???
	Location(double, double, float);
	virtual ~Location();

	double getEasting() { return easting; }
	double getNorthing() { return northing; }
	double getElevation() { return elevation; }

	void showLocation();
	bool isEqual(Location p);

	Location operator-(Location p);
	Location operator=(Location p);

private:
	double easting;
	double northing;
	float elevation;
};

#endif // !defined(AFX_LOCATION_H__2CC0FD2D_6689_11D6_A105_0050DA102704__INCLUDED_)
