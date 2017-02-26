#include "getInput.h"

/******************************************************************************
** NAME:				startup(char* fname, fstream& infile, int& ecode)
** DESCRIPTION:	Prompt user for input data file, open it.	If failure, ecode set
** 					ecountered open error
** PARAMETERS:		char* fname -
** 					fstream& infile -
** 					int& ecode -
** RETURN:			void - infile passed by reference - returned open and ready to use
******************************************************************************/
void startup(char* fname, fstream& infile, int& ecode)
{
	cout << "Enter name of file containing point set please:  ";

	cin.getline(fname, LONG_STR, '\n');
	infile.open(fname, ios::in);

	if(infile.rdstate() != 0)
	{
		cout << "\nUnable to open file: " << fname << endl;
		cout << "Did you forget to include the file extension (.txt) ?\n";
		ecode = infile.rdstate();
	}
}

/******************************************************************************
** NAME:				loadLocations(fstream& infile, vector<Location>& v)
** DESCRIPTION:	Invoked from main().	Run until eof() is reached,
** 					reading each Location from each line, and loading them into the
** 					vector passed in by reference.
** PARAMETERS:		fstream& infile - reference to open file.
** 					vector<Location>& v - Vector passed by reference. On ititial call of
** 					function, v is empty.  when the function is exited, the vector is loaded
** 					with all the points of the data set pointed to by infile.
** RETURN:			void - vector<Location> passed by reference returns vector containing all the
** 					points of the data set pointed to by infile.
** SIDE	EFFECTS:	none - But somewhat slow.	Expected load time
** 					for one hundred thousand points is roughly 14.5 seconds.
** 					Or an average of six to seven thousand points per second.
******************************************************************************/
void loadLocations(fstream& infile, vector<Location>& v)
{
	int ecode;
	char	 _v[SHORT_STR], _e[SHORT_STR], _n[SHORT_STR];
	double elevation=0, easting=0, northing=0;

	cout << "\nReading...";
	while(!infile.eof())
	{
		infile.getline(_e, SHORT_STR, ',');
		infile.getline(_n, SHORT_STR, ',');
		infile.getline(_v, SHORT_STR, '\n');

		elevation=atof (_v);
		easting=atof	(_e);
		northing=atof	(_n);

		Location p(elevation, easting, northing);

		ecode = infile.rdstate();
		if(!ecode)							// read successful?
			v.push_back(p);
	}

	quickSort(v, vCompare());
	vector<Location>::iterator new_end = unique(v.begin(), v.end());
	cout << "\nTotal points found: " << v.size() << endl << endl;
}

/******************************************************************************
** NAME:				finish
** DESCRIPTION:	open new output file for writing.	Write the data, and cleanup and close all
** 					open files.
** PARAMETERS:		fstream& infile - reference to input datafile.
** 					fstream& outfile - reference to output datafile.
** 					char* outname - name of the new output file to be created.
** 					vector<Location>& v - vector passed by referece for writing to
** 					output, and for cleanup.
******************************************************************************/
void finish(fstream& infile,
				fstream& outfile, char* outname, vector<Location>& v, Graph& T)
{
	int i=0;
	outfile.setf(ios::fixed);
	outfile.precision(3);
	double iE=0, xE=0, iN=0, xN=0;
	greatestSpatialExtent(v, iE, xE, iN, xN);

	cout << "\nEnter name of file to write:\n";
	cout << "Ensure that you include the file extension (.txt)  ";
	cin.getline(outname, LONG_STR, '\n');
	outfile.open(outname, (ios::out | ios::trunc));
	vector<Triangle> k;

	if(outfile.rdstate() != 0)
	{
		cout << "Unable to open file: " << outname << endl;
		cout << "Data cannot be written. " << endl;
	}
	else
	{
		cout << "\nWriting...";
		outfile << iE << ',' << xE << ',' << iN << ',' << xN << '\n';
		T.print(k);
		for(i=0; i<k.size(); i++)
			outfile << k[i] << endl; outfile.flush();
		cout << "\nData written successfully..." << endl;
	}

	infile.close(); outfile.close();
	cout << "\nFinished.\n";
}
