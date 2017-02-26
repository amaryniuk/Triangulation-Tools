#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <stdio.h>
#include <cmath>
#include "Location.h"
#include "LineEquation.h"

#define TOLERANCE 0.0001		// Define your own tolerance.
#define _TOLERANCE -0.0001
//#define DOUBLE_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

/******************************************************************************
** NAME: 	class Triangle
** ATTRIBUTES:		Location p1, p2, p3:  Three vertexes of a given triangle.
** 					Location pC:			A unique circle which passes exactly through all three
** 					double r:				points in the triangle.  The circle is expressed by a
** 												center point, and a radius.
** 					LineEquation P1, P2, P3:	The equations of the three lines (edges) of the triangle
** 														are expressed in the form Ax + By + C = 0.
** METHODS: 		Location getX () const	 Accessor methods for the three vertexes, and the center point.
** 					double	getR () const  Accessor method for the radius of the circle passing through
** 													the three vertexes.
** 					void hasEquations ()  Displays the equations of the three edges of the triangle.
** 					int contains (Location&) Queary point is inputed and an integer value is returned which
** 										represents weather the point lies within the triangle, on an edge
** 										of the triangle, or else outside of the triangle.  The integer is
** 										returned based on substituting the values of the queary point (ie,
** 										easting, northing) into each of the equations of each edge. The
** 										following determines the position of the triangle.
** 										if Ax + By + C < 0 for all three edges - Triangle contains pR - return -1
** 										else if Ax + By + C == 0 for a single edge - pR on Edge of Triangle - return 0
** 										else if Ax + By + C > 0 for any edge - pR outside of Triangle - return 1
** 			operator<<			Overloaded shift operator<<		: Displays Triangle to std out.
** 			operator=			Overloaded assignment operator= : Assigns all Triangle attributes of the rhs to lhs.
** 			operator==			Overloaded comparison operator==	: Return true if rhs equal to lhs.
** DEPENDENCIES:					class Location
** 									class LineEquation
******************************************************************************/
sclass Triangle
{
public:
	Triangle();
	Triangle(Location _p1, Location _p2, Location _p3);
	virtual ~Triangle();

	Location get1 () const { return p1; }
	Location get2 () const { return p2; }
	Location get3 () const { return p3; }
	Location getC () const { return pC; }
	double	getR () const { return r;	}

	void hasEquations ();
	int  contains(Location& pR);
	int  circleContains(Location& pR);

	friend ostream &operator<<(ostream& out, const Triangle& t);
	Triangle operator=(Triangle t);
	bool operator==(Triangle t);

private:
	Location p1, p2, p3;
	Location pC;
	double r;

	LineEquation P1;	// equation of line p2p3
	LineEquation P2;	// equation of line p1p3
	LineEquation P3;	// equation of line p1p2
};

#endif
