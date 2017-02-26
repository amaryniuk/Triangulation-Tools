#include "Triangle.h"

// Constructor:
Triangle::Triangle()
{
}

// Constructor: Sets the three fields to the three parameters.
// Finds the unique circle which passes exactly through all three points in the 
// triangle.  The circle is expressed by a center point, and a radius.	Note:
// The center point and radius are unique to the triangle, but may express 
// infinatly many triangles.
// Also, the equations of the three lines (edges) of the triangle as expressed
// in the form Ax + By + C = 0, and constants A, B, C can be accessed through
// methods getA, getB, getC.
Triangle::Triangle(Location _p1, Location _p2, Location _p3)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;

	double dx2 = p2.getEasting() - p1.getEasting();
	double dy2 = p2.getNorthing() - p1.getNorthing();
	double dr2 = dx2*dx2 + dy2*dy2;

	double dx3 = p3.getEasting() - p1.getEasting();
	double dy3 = p3.getNorthing() - p1.getNorthing();
	double dr3 = dx3*dx3 + dy3*dy3;

	double A  = 2 * (dx2 * dy3 - dx3 * dy2);
	double dx = (dr2 * dy3 - dr3 * dy2) / A;
	double dy = (dx2 * dr3 - dx3 * dr2) / A;

// One problem -- How to define the elevation for pC -- does it matter? -- So take the average.
	double aE = (p1.getElevation() + p2.getElevation() + p3.getElevation() ) / 3;

	pC = Location(aE , p1.getEasting() + dx, p1.getNorthing() + dy);
	r = sqrt(dx * dx + dy * dy);
	
	P1 = LineEquation(p2, p3); // equation of line p2p3
	P1.set(p1); 					// check and verify against p1

	P2 = LineEquation(p1, p3); // equation of line p1p3
	P2.set(p2); 					// check and verify against p2

	P3 = LineEquation(p1, p2); // equation of line p1p2
	P3.set(p3); 					// check and verify against p3
}

// Destructor: 
Triangle::~Triangle()
{
}

// Displays the equations of the three edges of the triangle.
void Triangle::hasEquations()
{
	cout << P1 << P2 << P3 << endl;
}

// We can determine if a query point pR is with the triangle *this using the following
// equations and their properties.
// if Ax + By + C < 0 for all three edges - Triangle contains pR
// else if Ax + By + C == 0 for a single edge - pR on Edge of Triangle
// else if Ax + By + C > 0 for any edge - pR outside of Triangle
int Triangle::contains(Location& pR)
{
	double edge1=0;  double edge2=0; double edge3=0;
	double A=0; 	  double B=0;		double C=0;
	double east  = pR.getEasting();
	double north = pR.getNorthing();

	A = P1.getA();
	B = P1.getB();
	C = P1.getC();
	edge1 = A*east + B*north + C;

	A = P2.getA();
	B = P2.getB();
	C = P2.getC();
	edge2 = A*east + B*north + C;

	A = P3.getA();
	B = P3.getB();
	C = P3.getC();
	edge3 = A*east + B*north + C;

//   cout << edge1 << endl << edge2 << endl << edge3 << endl;

	// Because of the natural inaccuracy of floating point precision, we allow for a small tolerance
	// when testing for zero.	The tolerance is defined in Triangle.h and is currently set to +-0.0001
	if(edge1>TOLERANCE || edge2>TOLERANCE || edge3>TOLERANCE)
		return 1;
	else if(edge1<_TOLERANCE && edge2<_TOLERANCE && edge3<_TOLERANCE)
		return -1;
	else return 0;
}

// return negative number if inside circle, positive if outside, 0 if on edge.
int Triangle::circleContains(Location& pR)
{
	double deltaEast=0;
	double deltaNorth=0;
	double distance=0;

	deltaEast = pR.getEasting() - pC.getEasting();
	deltaNorth = pR.getNorthing() - pC.getNorthing();

	distance = sqrt((deltaEast*deltaEast) + (deltaNorth*deltaNorth));

	// return negative number if inside circle, positive if outside, 0 if on edge.
	distance -= r;

	if(distance<0)
		return -1;
	else if(distance == 0)
		return 0;
	else
		return 1;
}

// Overloaded shift operator<< : Displays Triangle to std out.
ostream &operator<<(ostream& out, const Triangle& t)
{
	cout.setf(ios::fixed);
	cout.precision(3);
	return out << t.get1() << '|' << t.get2() << '|' << t.get3();
}

// Overloaded assignment operator= : Assigns all Triangle 
// attributes of the rhs to lhs.
Triangle Triangle::operator=(Triangle t)
{
	p1 = t.p1;	p2 = t.p2;	p3 = t.p3;		// vertexes
	pC = t.pC;	r	= t.r;						// circle
	P1 = t.P1;	P2 = t.P2;	P3 = t.P3;		// equations
	return *this;
}

// Overloaded comparison operator== : Return true if rhs equal to lhs.
bool Triangle::operator==(Triangle t)
{
	if(p1==t.p1)
		if(p2==t.p2)
			if(p3==t.p3)
				return true;
	return false;
}
