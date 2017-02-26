#include "spatial.h"

/******************************************************************************
** NAME:				double greatestSpatialExtent(vector<Location&, double&, double&,
** 													 double&, double&);
** DESCRIPTION:	Returns (by reference) the full spatial extent of the provided
** 					vector of Locations.  In other words, The coordinates of the
** 					furthest east/west/north/south point is returned.
** DEPENDENCIES:	Call to these functions within spatialExtent()
** 					void eExtent(vector<Location>& v, double& minE, double& maxE);
** 					void nExtent(vector<Location>& v, double& minN, double& maxN);
** PARAMETERS:		double& MIN_COORD, double& MAX_COORD
** 					After return, the min/max coordinates of both east/west, and
** 					north/south are stored as the original parameters passed in.
** RETURN:			double	- greatest maximum dimension from a theoretical center point
**									- MIN/MAX passed by reference - returned as original parameters.
******************************************************************************/
double greatestSpatialExtent(vector<Location>& v, double& minE, double& maxE,
																  double& minN, double& maxN)
{
	eExtent(v, minE, maxE);
	nExtent(v, minN, maxN);

	double E = 0.5 * (maxE - minE);
	double N = 0.5 * (maxN - minN);
	return (N >= E) ? N : E;
}

/******************************************************************************
** NAME: void vExtent(vector<Location>& v, double& minV, double& maxV);
** 		void eExtent(vector<Location>& v, double& minE, double& maxE);
** 		void nExtent(vector<Location>& v, double& minN, double& maxN);
** DESCRIPTION:	Returns the minimum and maximum coordinate (or elevations)
** 					of each attibute of the vector of Locaitons.
** PARAMETERS:		double& MIN_COORD, double& MAX_COORD
** 					After return, the min/max elevation of the data set, and the min/max
** 					coordinates of both east/west, and north/south are stored as
** 					the original parameters passed in.
** DEPENDENCIES:	quickSelect(vector<Object>&, Comparator);
******************************************************************************/
void vExtent(vector<Location>& v, double& minV, double& maxV)
{
	long last = v.size()-1;

	quickSelect(v, 0, vCompare());
	minV = v[0].getElevation();

	quickSelect(v, last, vCompare());
	maxV = v[last].getElevation();

// cout << "MinV = " << minV << "\tMaxV = " << maxV << endl;
}

void eExtent(vector<Location>& v, double& minE, double& maxE)
{
	long last = v.size()-1;

	quickSelect(v, 0, eCompare());
	minE = v[0].getEasting();

	quickSelect(v, last, eCompare());
	maxE = v[last].getEasting();
// cout << "MinE = " << minE << "\tMaxE = " << maxE << endl;
}

void nExtent(vector<Location>& v, double& minN, double& maxN)
{
	long last = v.size()-1;

	quickSelect(v, 0, nCompare());
	minN = v[0].getNorthing();

	quickSelect(v, last, nCompare());
	maxN = v[last].getNorthing();
// cout << "MinN = " << minN << "\tMaxN = " << maxN << endl;
}

/******************************************************************************
** NAME: long medV(vector<Location>& v);
** 		long medE(vector<Location>& v);
** 		long medN(vector<Location>& v);
** DESCRIPTION:	Given a vector of Locations, each method returns the median value
** 					of the elevation, easting, northing (respective to each function)
** 					for the given data set.
** MODIFICATION:	Each function now makes calls to quickSelect rather that quickSort.
** 					Since this function would have most likely been the bottleneck
** 					of the program, a new (half)sort routine was created which instead
** 					of sorting the entire vector, it "selects" which parts need
** 					to be sorted, and which do not, which is considerably more time efficient.
** 					For futher details, see the documentation for quickSelect.
** DEPENDENCIES:	quickSelect(vector<Object>&, Comparator);
** PARAMETERS:		Vector passed by reference.
**
** RETURN:			double integer - Index into the vector represents the point at
** 					which the median value is stored.
******************************************************************************/
long medV(vector<Location>& v)
{
	long i=0;
	long last = v.size()-1;
	long medV = long(0.5 * last);

	quickSelect(v, vCompare());
	for(i=medV; i<last; i++)
		if(v[i+1].getElevation() == v[medV].getElevation())
			medV++;
		else break;
	return medV;	// return _index_ of the median value -- NOT the median value
}

long medE(vector<Location>& v)
{
	long i=0;
	long last = v.size()-1;
	long medE = long(0.5 * last);

	quickSelect(v, eCompare());
	for(i=medE; i<last; i++)
		if(v[i+1].getEasting() == v[medE].getEasting())
			medE++;
		else break;
	return medE;	// return _index_ of the median value -- NOT the median value
}

long medN(vector<Location>& v)
{
	long i=0;
	long last = v.size()-1;
	long medN = long(0.5 * last);

	quickSelect(v, nCompare());
	for(i=medN; i<last; i++)
		if(v[i+1].getNorthing() == v[medN].getNorthing())
			medN++;
		else break;
	return medN;	// return _index_ of the median value -- NOT the median value
}
