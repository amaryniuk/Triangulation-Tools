#include "findIntervals.h"

/***********************************************************
** Description:  Since the STL sine function returns the sine of a
** angle in RADIANS, (and we want degrees) a constant ( PI / 180 ) is
** multiplied to the angle prior to taking the sine of the angle.
*************************************************************/
double getIncreaceEasting(int sizeOfInterval, double azimuth)
{
	const double pi_over_180 = 0.01745329;
	double increaceEasting = 0;

	// Gets the sine of azimuth, in degrees rather than radians.
	azimuth = azimuth*pi_over_180;
	azimuth = sin(azimuth);

	increaceEasting = sizeOfInterval*azimuth;
	return increaceEasting;
}

/***********************************************************
** Description:  Since the STL cosine function returns the cosine of a
** angle in RADIANS, (and we want degrees) a constant ( PI / 180 ) is
** multiplied to the angle prior to cosine(ing) the angle.
*************************************************************/
double getIncreaceNorthing(int sizeOfInterval, double azimuth)
{
	const double pi_over_180 = 0.01745329;
	double increaceNorthing = 0;

	// Gets the cosine of azimuth, in degrees rather than radians.
	azimuth = azimuth*pi_over_180;
	azimuth = cos(azimuth);

	increaceNorthing = sizeOfInterval*azimuth;
	return increaceNorthing;
}

void getIntervals(Location p1, double distance, double azimuth, int sizeOfInterval)
{
	int numberOfIntervals = distance/sizeOfInterval;
	double easting = p1.getEasting();
	double northing = p1.getNorthing();
	const double increaceEasting = getIncreaceEasting(sizeOfInterval, azimuth);
	const double increaceNorthing = getIncreaceNorthing(sizeOfInterval, azimuth);

	cout << "Number of Stations = " << numberOfIntervals << endl;

	cout.precision(9);
	cout << "Easting: " << easting << ",\tNorthing: " << northing << endl;

	for(int i=1; i<numberOfIntervals; i++)
	{
		easting += increaceEasting;
		northing += increaceNorthing;
		cout.precision(9);
		cout << "Easting: " << easting << "  \tNorthing: " << northing << endl;
	}
}
