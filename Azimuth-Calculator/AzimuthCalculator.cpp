#include "AzimuthCalculator.h"

int main()
{
	int sizeOfInterval = 60;
	double tempEasting=0, tempNorthing=0, distance=0, azimuth=0;

	cout << "\n\t\tAzimuth Calculator\n\n";
	cout << "Enter First Location: \nEasting: ";
	cin >> tempEasting;
	cout << "Northing: ";
	cin >> tempNorthing;
	Location p1(tempEasting, tempNorthing);
	cout << "Enter Second Location: \nEasting: ";
	cin >> tempEasting;
	cout << "Northing: ";
	cin >> tempNorthing;
	Location p2(tempEasting, tempNorthing);

	distance = calculateDistance(p1, p2);
	azimuth = calculateAzimuth(p1, p2);
	cout << "\nDistance between p1 and p2 is " << distance << " m. \n";
	cout << "Azimuth is "<< azimuth << " degrees. " << endl << endl;

	cout << "Enter Station Interval (metres): ";
	cin >> sizeOfInterval;

	getIntervals(p1, distance, azimuth, sizeOfInterval);

	int i;
	cin >> i;
	return 0;

}
