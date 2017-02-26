#include "LineEquation.h"

// Construction/Destruction
LineEquation::LineEquation()
{
}

// Each edge of a triangle has a unique equation that can be expressed
// by as Ax + By + C.  This is another way to express the equation y=mx+b.  From these
// equations, the slope and yIntercept of the line can be determined.  These equations
// can also be used to determine if a point (A, B) is on one side or on the other of the line
// described by the equation.  If we repeat this for each edge in the triangle, we can determine
// if the point is within, or outside (as well as on the edge of) the triangle.
LineEquation::LineEquation(Location p1, Location p2)
{
	double dx = p2.getEasting()  - p1.getEasting();
	double dy = p2.getNorthing() - p1.getNorthing();

	if(!dx)			// if vertical
	{
		A = 1;
		B = 0;
		C = -p1.getEasting();
	}
	else if(!dy)	// if horizontal
	{
		A = 0;
		B = 1;
		C = -p1.getNorthing();
	}
	else				// all others
	{
		A = dy;
		B = -dx;
		C = dx*p1.getNorthing() - dy*p1.getEasting();
	}
}

LineEquation::~LineEquation()
{
}

// In order to determine if a point is within a triangle, the equation must have the property
// that the third point A, B when pluged into the equation is a negative value.
void LineEquation::set(Location pR)
{
	double val = A * pR.getEasting() + B * pR.getNorthing() + C;
	if(val >= 0)
	{
		A = -A;	B = -B;	C = -C;
	}
}

ostream &operator<<(ostream& out, const LineEquation& eq)
{
	cout.setf(ios::fixed);
	cout.precision(3);
	return out
		<< "("		<< eq.getA()
		<< ")x + (" << eq.getB()
		<< ")y + (" << eq.getC() << ") = 0" << endl;
}
