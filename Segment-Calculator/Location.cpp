// Location.cpp: implementation of the Location class.

#include "Location.h"

// Construction/Destruction
Location::Location()
{
	easting = northing = elevation = 0;
}

Location::~Location()
{

}
/*
Location::Location(double ea, double no)
{
	easting = ea;
	northing = no;
	elevation = 0;
}
*/

Location::Location(double ea, double no, float el)
{
	easting = ea;
	northing = no;
	elevation = el;
}

void Location::showLocation()
{
	cout << "Easting: " << easting;
	cout << "\tNorthing: " << northing;
	cout << "\tElevation: " << elevation << endl;
}

bool Location::isEqual(Location p)
{
	if(easting == p.getEasting())
		if(northing == p.getNorthing())
			if(elevation == p.getElevation())
				return true;
	return false;
}

Location Location::operator-(Location p)
{
	Location temp;

	temp.easting = easting - p.getEasting();
	temp.northing = northing - p.getNorthing();
	temp.elevation = elevation - p.getElevation();

	return temp;
}

Location Location::operator=(Location p)
{
	easting = p.getEasting();
	northing = p.getNorthing();
	elevation = p.getElevation();

	return *this;
}
