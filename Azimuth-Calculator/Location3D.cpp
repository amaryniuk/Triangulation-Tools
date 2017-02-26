#include "Location3D.h"

Location3D::Location3D()
{
	easting = northing = elevation = 0;
}

Location3D::Location3D(double ea, double n, double el)
{
	easting = ea;
	northing = n;
	elevation = el;
}

void Location3D::showLocation()
{
	cout << "Easting: " << easting;
	cout << "\tNorthing: " << northing;
	cout << "\tElevation: " << elevation << endl;
}

bool Location3D::isEqual(Location3D p)
{
	if(easting == p.getEasting())
		if(northing == p.getNorthing())
			if(elevation == p.getElevation())
				return true;
	return false;
}
/*
// The Location returned has northing/easting/elevation representative
// of the differnce between the northing/easting/elevation of the two points
Location3D Location3D::operator-(Location3D p)
{
	Location3D temp;

	temp.easting = easting - p.easting;
	temp.northing = northing - p.northing;
	temp.elevation = elevation - p.elevation;

	return temp;
}

// Assignment of one Location3D to another.
Location3D Location3D::operator=(Location3D p)
{
	easting = p.easting;
	northing = p.northing;
	elevation = p.elevation;
	return *this;
}
*/