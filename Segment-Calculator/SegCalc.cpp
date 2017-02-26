#include "SegCalc.h"

int main()
{
	int sizeOfInterval = 60;

	double	tmpEasting=0;
	double	tmpNorthing=0;
	float	tmpElevation=0;

	double	horizontal=0;	// horizontal distance between two points
	double	azimuth=0;		// azimuth from one point to another (degrees)
	double	slopeDistance;	// slope distance between two points
	double	slopeAngle;		// angle (in degrees) to next location w/ 0(deg) as horizon, and zenith as 90(deg)  max range is +90 -> -90

	char i;
	while(i!='n')
	{
	cout << "\n\t\tSegCalc.exe\n\n";
/*	cout << "Enter First Location:\n";
	cout << "Easting: "; cin >> tmpEasting;
	cout << "Northing: "; cin >> tmpNorthing;
	cout << "Elevation: "; cin >> tmpElevation;
	Location p1(tmpEasting, tmpNorthing, tmpElevation);
*/
	Location p1(0, 0, 0);

	cout << "Enter Second Location: ";
	cout << "\nEasting: "; cin >> tmpEasting;
	cout << "Northing: "; cin >> tmpNorthing;
	cout << "Elevation: "; cin >> tmpElevation;
	Location p2(tmpEasting, tmpNorthing, tmpElevation);

//************************************

	horizontal = calcHorizontal(p1, p2);
	azimuth = calcAzimuth(p1, p2);
	slopeDistance = calcSlope(p1, p2);
	slopeAngle = calcElevation(p1, p2);

	cout << "\nHorizontal Distance between p1 and p2 is " << horizontal << " m. \n";
	cout << "Azimuth is "<< azimuth << " degrees. " << endl;

	cout << "\nSlope Distance between p1 and p2 is " << slopeDistance << " m. \n";
	cout << "Elevation is "<< slopeAngle << " degrees. " << endl << endl;

//	cout << "Enter Station Interval (metres): ";
//	cin >> sizeOfInterval;
//	Location next = nextStation_Horizontal(p1, horizontal, azimuth, sizeOfInterval);
//	next.showLocation();

	cout << "\nAgain(y/n) "; cin >> i;
	}

	return 0;
}
