#ifndef _LINE_EQUATION_H_
#define _LINE_EQUATION_H_

#include "Location.h"

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** NAME: 			class LineEquation
** ATTRIBUTES: 	double A, B, C
** METHODS: 		Double getX () const Accessor methods for the three vertexes, and the center point.
** 					void set(Location)	Establishes a direction for the vector based on the coordinates of the
** 												third vertex in the triangle.
** 					void flip ()			Flips the signs of the constants if nessasary.	This is determined within the set method.
** 					operator<<		Overloaded shift operator<<:	Displays LineEquation to std out.
** DEPENDENCIES:	class Location
******************************************************************************/
class LineEquation
{
public:
	LineEquation();
	LineEquation(Location p1, Location p2);
	virtual ~LineEquation();

	double getA() const { return A; }
	double getB() const { return B; }
	double getC() const { return C; }

	void set(Location pR);
	friend ostream &operator<<(ostream& out, const LineEquation& eq);

private:
	double A, B, C;
};

#endif
