#include "Location.h"

Location::Location()
{
	easting = northing = 0;
}

Location::Location(double e, double n)
{
	easting = e;
	northing = n;
}

void Location::showLocation()
{
	cout << "Easting: " << easting;
	cout << "\tNorthing: " << northing << endl;
}

bool Location::isEqual(Location p)
{
	if(easting == p.getEasting())
		if(northing == p.getNorthing())
			return true;
	return false;
}

// The Location returned has northing/easting representative
// of the differnce between the northing/easting of the two points
Location Location::operator-(Location p)
{
	Location temp;

	temp.easting = easting - p.easting;
	temp.northing = northing - p.northing;

	return temp;
}

// Assignment of one Location to another.
Location Location::operator=(Location p)
{
	easting = p.easting;
	northing = p.northing;
	return *this;
}
