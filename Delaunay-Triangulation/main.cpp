#include <fstream>
#include <vector>
#include <time.h>
#include <conio.h>

#include "getInput.h"
#include "Delaunay.h"

int main()
{
	fstream infile;
	fstream outfile;
	char fname[LONG_STR];
	char outname[LONG_STR];

	// Other Locals
	int i=0, ecode=0;
	double time=0, start=0, end=0;
	vector<Location> v;
	Graph T;

	cout.setf(ios::fixed);
	cout.precision(3);

	startup(fname, infile, ecode);

	if (ecode)	// open successful?
	{
		cout << "\n\nFatal error encountered: File IO error: " << ecode;
		cout << "\nBailing out.\n\nPress any key to continue.";
		while(1)
			if(kbhit())
				break;
		exit(-1);
	}

	loadLocations(infile, v);
// for(i=0; i<v.size(); i++)
// 	cout << v[i] << endl; cout.flush(); cout << endl;

	start=clock();

	DelaunayTriangulation(v, T);

	end=clock(); time=end-start; time/=CLOCKS_PER_SEC;
	cout << "\nTime: " << time << "s\n\n";

// T.print();

	finish(infile, outfile, outname, v, T);

	cout << "Press any key to continue";
	while(1)
		if(kbhit())
			break;
	return 0;
}
