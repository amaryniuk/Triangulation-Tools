#include <fstream>
#include <vector>
#include <time.h>
#include <conio.h>

#include "getInput.h"
#include "populateLines.h"
#include "Station.h"
#include "Queary.h"

int main()
{
	// File IO Stuff
	fstream infile;
	fstream infile2;
	fstream outfile;
	char fname[LONG_STR];
	char outname[LONG_STR];
	double spatialExtent[3];

	// Other Locals
	int i=0, ecode=0;
	double time=0, start=0, end=0;
	vector<Triangle> T;
	vector<Station> S;
	vector<Queary> Q;

	cout.setf(ios::fixed);
	cout.precision(3);

	startup(fname, infile, infile2, ecode);

	if (ecode)	// open successful?
	{
		cout << "\n\nFatal error encountered: File IO error: " << ecode;
		cout << "\nBailing out.\n\nPress any key to continue.";
		while(1)
			if(kbhit())
				break;
		exit(-1);
	}

	loadLocations(infile, spatialExtent, T);
	loadQuearyFile(infile2, Q);

//	for(i=0; i<T.size(); i++)
//		cout << T[i] << endl;

//	cout << endl << endl << endl;

//	for(i=0; i<Q.size(); i++)
//		cout << Q[i] << endl;

	quickSort(T, tri1East());
	populateLines(T, spatialExtent, S, Q);

	finish(infile, infile2, outfile, outname, S);

	cout << "Press any key to continue";
	while(1)
		if(kbhit())
			break;
	return 0;
}
