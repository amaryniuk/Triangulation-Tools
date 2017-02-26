#include "getInput.h"

/******************************************************************************
** NAME:				startup(char* fname, fstream& infile, int& ecode)
** DESCRIPTION:	Prompt user for input data file, open it.	If failure, ecode set
** 					ecountered open error
** PARAMETERS:		char* fname
** 					fstream& infile
** 					int& ecode
** RETURN:			void - infile passed by reference - returned open and ready to use
******************************************************************************/
void startup(char* fname, fstream& infile, fstream& infile2, int& ecode)
{
	cout << "Enter name of file containing point set please:  ";

	cin.getline(fname, LONG_STR, '\n');
	infile.open(fname, ios::in);

	if(infile.rdstate() != 0)
	{
		cout << "\nUnable to open file: " << fname << endl;
		cout << "Did you forget to include the file extension (.txt) ?\n";
		ecode = infile.rdstate();
		return;
	}

	cout << "Enter name of file containing Quearies:  ";

	cin.getline(fname, LONG_STR, '\n');
	infile2.open(fname, ios::in);

	if(infile2.rdstate() != 0)
	{
		cout << "\nUnable to open file: " << fname << endl;
		cout << "Did you forget to include the file extension (.txt) ?\n";
		ecode = infile.rdstate();
		return;
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
void loadLocations(fstream& infile, double* x, vector<Triangle>& T)
{
	int ecode;
	int i=0;
	char	 _num[SHORT_STR];
	char	 _v[SHORT_STR], _e[SHORT_STR], _n[SHORT_STR];
	double v1=0, e1=0, n1=0;
	double v2=0, e2=0, n2=0;
	double v3=0, e3=0, n3=0;

	cout << "\nReading...";
	for(i=0; i<3; i++)
	{
		infile.getline(_num, SHORT_STR, ',');
		x[i] = atof(_num);
	}
	infile.getline(_num, SHORT_STR, '\n');
	x[3] = atof(_num);

	while(!infile.eof())
	{
		infile.getline(_e, SHORT_STR, ',');
		infile.getline(_n, SHORT_STR, ',');
		infile.getline(_v, SHORT_STR, '|');
		e1=atof (_e); n1=atof (_n); v1=atof (_v);
		Location p1(v1, e1, n1);

		infile.getline(_e, SHORT_STR, ',');
		infile.getline(_n, SHORT_STR, ',');
		infile.getline(_v, SHORT_STR, '|');
		e2=atof (_e); n2=atof (_n); v2=atof (_v);
		Location p2(v2, e2, n2);

		infile.getline(_e, SHORT_STR, ',');
		infile.getline(_n, SHORT_STR, ',');
		infile.getline(_v, SHORT_STR, '\n');
		e3=atof (_e); n3=atof (_n); v3=atof (_v);
		Location p3(v3, e3, n3);

		if(p3.getEasting()<p2.getEasting())
			p3.swap(p2);
		if(p2.getEasting()<p1.getEasting())
			p1.swap(p2);
		if(p3.getEasting()<p2.getEasting())
			p3.swap(p2);

		Triangle t (p1,p2,p3);

		ecode = infile.rdstate();
		if(!ecode)							// read successful?
			T.push_back(t);
	}
	cout << "\nTotal triangles found: " << T.size() << endl << endl;
}

void loadQuearyFile(fstream& infile2, vector<Queary>& Q)
{
	int ecode;
	int i=0;
	int stnNum=0;
	char	 lineName[LONG_STR];

	char	 _stnNum[SHORT_STR];
	char	 _e[SHORT_STR], _n[SHORT_STR];
	double e=0, n=0;
	Location p1(0,0,0);
	Location p2(0,0,0);
	Queary q(lineName, 0, p1, p2);

	while(!infile2.eof())
	{
		infile2.getline(lineName, LONG_STR, ',');
		infile2.getline(_stnNum, SHORT_STR, ',');
		stnNum = atoi(_stnNum);

		infile2.getline(_e, SHORT_STR, ',');
		infile2.getline(_n, SHORT_STR, ',');
		e=atof (_e); n=atof (_n);
		p1.setEasting(e); p1.setNorthing(n);

		infile2.getline(_e, SHORT_STR, ',');
		infile2.getline(_n, SHORT_STR, '\n');
		e=atof (_e); n=atof (_n);
		p2.setEasting(e); p2.setNorthing(n);

		q.setLineName(lineName);
		q.setLineNum(stnNum);
		q.setBOL(p1);
		q.setEOL(p2);

		ecode = infile2.rdstate();
		if(!ecode)							// read successful?
			Q.push_back(q);
	}
}

/******************************************************************************
** NAME: 		 finish
** DESCRIPTION: open new output file for writing.	Write the data, and cleanup and close all
** 				 open files.
** PARAMETERS:  fstream& infile - reference to input datafile.
** 				 fstream& outfile - reference to output datafile.
** 				 char* outname - name of the new output file to be created.
** 				 vector<Station>& v - vector passed by referece for writing to
** 				 output, and for cleanup.
******************************************************************************/
void finish(fstream& infile, fstream& infile2, fstream& outfile, char* outname, vector<Station>& S)
{
	int i=0;
	outfile.setf(ios::fixed);
	outfile.precision(3);
	char junk;

	cin.get(junk);
	cout << "\nEnter name of file to write:\n";
	cout << "Ensure that you include the file extension (.txt)  ";
	cin.getline(outname, LONG_STR, '\n');
	outfile.open(outname, (ios::out | ios::trunc));

	if(outfile.rdstate() != 0)
	{
		cout << "Unable to open file: " << outname << endl;
		cout << "Data cannot be written. " << endl;
	}
	else
	{
		cout << "\nWriting...";
		for(i=0; i<S.size(); i++)
			outfile << S[i] << endl;
		outfile.flush();

		cout << "\nData written successfully..." << endl;
	}

	infile.close(); infile2.close(); outfile.close();
	cout << "\nFinished.\n";
}
