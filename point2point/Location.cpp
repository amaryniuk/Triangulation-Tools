#include "Location.h"

// Constructor: sets the three fields to the NULL
Location::Location()
{
	elevation = 0;
	easting	 = 0;
	northing  = 0;
}

// Constructor: sets the three fields to the three given values
Location::Location(double _v, double _e, double _n)
{
	elevation =  _v;
	easting	 =  _e;
	northing  =  _n;
}

// Destructor: 
Location::~Location()
{
}

void Location::swap(Location& p)
{
	double temp=0;
	temp=p.getEasting(); p.setEasting(easting); easting=temp;
	temp=p.getNorthing(); p.setNorthing(northing); northing=temp;
	temp=p.getElevation(); p.setElevation(elevation); elevation=temp;
}

// Overloaded shift operator<< :  Displays Location to std out.
ostream &operator<<(ostream& out, const Location& p)
{
	cout.setf(ios::fixed);
	cout.precision(3);
	return out << p.getEasting() << ',' << p.getNorthing() << ',' << p.getElevation();
}

// Overloaded assignment operator= : Assigns all Location 
// attributes of the rhs to lhs.
Location Location::operator=(Location p)
{
	easting	 = p.getEasting();
	northing  = p.getNorthing();
	elevation = p.getElevation();
	return *this;
}

// Overloaded comparison operator== : Return true if rhs equal to lhs.
bool Location::operator==(Location p)
{
	if(DOUBLE_EQ(easting, p.easting))
		if(DOUBLE_EQ(northing, p.northing))
			return true;
	return false;
}

bool Location::operator!=(Location p)
{
	if(DOUBLE_EQ(easting, p.easting))
		if(DOUBLE_EQ(northing, p.northing))
			return false;
	return true;
}
