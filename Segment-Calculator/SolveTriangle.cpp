#include "SolveTriangle.h"

/***********************************************************
** Description:  Returns the distance between two points
** passed in using the pythagorean theorem.  This function
** currently only supports the distance between two edges on a
** 2-dimensional plane.  The function can(will) be overloaded to
** calculate the hypotenues in 3-dimensional space (ie,
** to include elevation)
*************************************************************/
double calcHorizontal(Location p1, Location p2)
{
	double	x=0,
			y=0,
			hyp=0;
	Location temp;

	temp = p1 - p2;

	x = temp.getEasting();
	y = temp.getNorthing();

	// find (delta)easting and (delta)northing and take
	// square root of the sum of squares
	hyp = sqrt( (x*x) + (y*y) );

	return hyp;
}

/************************************************************
** Description: By passing in two points on a 2-dimensional
** plane, this function determines the quadrant in which the
** second point(relative to the first) lies.  This method can(will)
** be overloaded to account for change in elevation (slope).
*************************************************************/
int getQuadrant(Location p1, Location p2)
{
	double x1, x2, y1, y2;
	x1 = p1.getEasting();
	x2 = p2.getEasting();
	y1 = p1.getNorthing();
	y2 = p2.getNorthing();

	if(x2>x1)
	{
		if(y2>y1)			// to EAST && NORTH
			return 0;
		else
			return 90;		// or to EAST && SOUTH
	}						//  ||  to direct EAST
	else if(x2<x1)
	{
		if(y2<y1)			// to WEST && SOUTH
			return 180;
		else
			return 270;		// to WEST && NORTH
	}						//  ||  to direct WEST
	else // x1 == x2
	{
		if(y2>y1)
			return 0;		// to direct NORTH
		else
			return 180;		// to direct SOUTH
	}
}

/***********************************************************
** Description:  Calculates the azimuth (or bearing) from one
** point (geographic location in UTM's) to another.
*************************************************************/
double calcAzimuth(Location p1, Location p2)
{
	int quad = 0;
	Location temp;
	double deltaEast, deltaNorth, theta=0;
	const double rad_to_deg = 57.29578;

	if(p1.isEqual(p2))
	{
		cout << "\nCannot compute azimuth of identical points.\n";
		return -1;
	}
	// to calc azimuth, determine which quadrent point p2 is in
	quad = getQuadrant(p1, p2);

	// get delta East / delta West, and take abs. val. **Note: c++ abs casts to int
	temp = p1 - p2;
	deltaEast = temp.getEasting(); deltaEast = sqrt(deltaEast*deltaEast);
	deltaNorth = temp.getNorthing(); deltaNorth = sqrt(deltaNorth*deltaNorth);

	// the method of caculating the angle differs with which quadrant the point is in
	if(quad==0 || quad==180)
		theta = deltaEast/deltaNorth;		// angle = (delta) E / (delta) N
	else // (quad == 90 || quad==270)
		theta = deltaNorth/deltaEast;		// angle = (delta) N / (delta) E

	theta = sqrt(theta*theta);				// get absolute value of angle
	theta = atan(theta)*rad_to_deg;
	theta = theta + quad;					// add either 0, 90, 180, 270 to obtain azimuth

	return theta;							// return the tan^(-1) (angle) in Degrees
}

double calcSlope(Location p1, Location p2)
{
	double	x=0,
			y=0,
			z=0,
			hyp=0;
	Location temp;

	temp = p1 - p2;

	x = temp.getEasting();
	y = temp.getNorthing();
	z = temp.getElevation();

	hyp = sqrt( (x*x) + (y*y) + (z*z) );

	return hyp;
}

double calcElevation(Location p1, Location p2)
{
	double	horiz=0,
			slope=0,
			theta=0;
	const double rad_to_deg = 57.29578;

	horiz = calcHorizontal(p1, p2);
	slope = calcSlope(p1, p2);

	theta = acos(horiz/slope)*rad_to_deg;

	if(slopeIsNegative(p1.getElevation(), p2.getElevation()))
		theta *= -1;

	return theta;
}

bool slopeIsNegative(double h1, double h2)
{
	if(h1>h2)
		return true;
	return false;
}
