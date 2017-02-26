#include "DetermineStations.h"

/***********************************************************
** Title:	double getIncreaceEasting(int sizeOfInterval, double azimuth)
**			double getIncreaceNorthing(int sizeOfInterval, double azimuth)
**			double getIncreaceElevation(int sizeOfInterval, double slopeAngle)
** Description:  The following functions return the change in easting,
** northing, and elevation (respectivly with each function) based on
** a given angle (azimuth for easting/northing, and a slopeAngle (or dip)
** for the elevation).
** *Note* Since the STL uses Radians (and we want degrees) a constant
** ( PI / 180 ) is multiplied to the angle prior to (cos)sine the angle.
** *Note*  pi_over_180 ~= 0.01745329  and is defined in DetermineStations.h
*************************************************************/
double getIncreaceEasting(double azimuth, int sizeOfInterval)
{
	double increaceEasting = 0;

	// Gets the sine of azimuth, in degrees rather than radians.
	azimuth = azimuth*pi_over_180;
	azimuth = sin(azimuth);

	increaceEasting = sizeOfInterval*azimuth;
	return increaceEasting;
}

double getIncreaceNorthing(double azimuth, int sizeOfInterval)
{
	double increaceNorthing = 0;

	// Gets the cosine of azimuth, in degrees rather than radians.
	azimuth *= pi_over_180;
	azimuth = cos(azimuth);

	increaceNorthing = sizeOfInterval*azimuth;
	return increaceNorthing;
}

double getIncreaceElevation(double slopeAngle, int sizeOfInterval)
{
	double increaceElevation = 0;

	// Gets the sine of azimuth, in degrees rather than radians.
	slopeAngle *= pi_over_180;
	slopeAngle = sin(slopeAngle);

	increaceElevation = sizeOfInterval*slopeAngle;

	return increaceElevation;
}

Location nextStation(Location p1, double horizontal, double azimuth, int sizeOfInterval)
{
	//int numberOfIntervals = horizontal/sizeOfInterval;
	double easting = p1.getEasting();
	double northing = p1.getNorthing();
	double elevation = p1.getElevation();

	// *** I dont know if i like this... *** Inefficient ***
	/* Solution:	Implement this so getIncreace[Easting/Northing/Elevation] is
					called once. Do this using the commented section below.  Store
					each point in some type of data struct */

	const double increaceEasting = getIncreaceEasting(azimuth, sizeOfInterval);
	const double increaceNorthing = getIncreaceNorthing(azimuth, sizeOfInterval);

	easting += increaceEasting;
	northing += increaceNorthing;

	Location next(easting, northing, elevation);
	return next;

/*	cout << "Number of Stations = " << numberOfIntervals << endl;
	cout.precision(9);
	cout << "Easting: " << easting << ",\tNorthing: " << northing << endl;

	for(int i=1; i<numberOfIntervals; i++)
	{
		easting += increaceEasting;
		northing += increaceNorthing;
		cout.precision(9);
		cout << "Easting: " << easting << "  \tNorthing: " << northing << endl;
	} */
}

Location nextStation(Location p1, double slopeDistance, double slopeAngle, double azimuth, int sizeOfInterval)
{
	//int numberOfIntervals = slopeDistance/sizeOfInterval;
	double easting = p1.getEasting();
	double northing = p1.getNorthing();
	double elevation = p1.getElevation();

	// *** See Above !!!
	const double increaceEasting = getIncreaceEasting(azimuth, sizeOfInterval);
	const double increaceNorthing = getIncreaceNorthing(azimuth, sizeOfInterval);
	const double increaceElevation = getIncreaceElevation(slopeAngle, sizeOfInterval);

	easting += increaceEasting;
	northing += increaceNorthing;
	elevation += increaceElevation;

	Location next(easting, northing, elevation);
	return next;
}
