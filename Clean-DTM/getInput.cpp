#include "getInput.h"

/******************************************************************************
** NAME:  startup(char* fname, fstream& infile, int& ecode)
** DESCRIPTION:  Prompt user for input data file, open it.  If failure, ecode set
**				 ecountered open error
** PARAMETERS:  char* fname -
**				fstream& infile -
**				int& ecode -
** RETURN:  void - infile passed by reference - returned open and ready to use
******************************************************************************/
void startup(char* fname, fstream& infile, int&	ecode)
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
** NAME:  loadLocations(fstream& infile, vector<Location>& v)
** DESCRIPTION:  Invoked from main().  Run until eof() is reached,
**				 reading each Location from each line, and loading them into the
**				 vector passed in by reference.
** PARAMETERS:  fstream& infile - reference to open file.
**				vector<Location>& v - Vector passed by reference. On ititial call of
**				function, v is empty.  when the function is exited, the vector is loaded
**				with all the points of the data set pointed to by infile.
** RETURN:  void - vector<Location> passed by reference returns vector containing all the
**				   points of the data set pointed to by infile.
** SIDE  EFFECTS: none - But somewhat slow.  Expected load time
**						 for one hundred thousand points is roughly 14.5 seconds.
**						 Or an average of six to seven thousand points per second.
******************************************************************************/
void loadLocations(fstream& infile, vector<Location>& v)
{
  int ecode;
  char _v[SHORT_STR], _e[SHORT_STR], _n[SHORT_STR];
  double elevation=0, easting=0, northing=0;

  cout << "\nReading...";

  while(!infile.eof())
  {
    infile.getline(_e, SHORT_STR, ',');
    infile.getline(_n, SHORT_STR, ',');
    infile.getline(_v, SHORT_STR, '\n');

    easting=atof(_e);
    northing=atof(_n);
    elevation=atof(_v);

    Location p(elevation, easting, northing);

    ecode = infile.rdstate();
    if(!ecode)									// read successful?
    v.push_back(p);
  }
  cout << "\nTotal points found: " << v.size() << endl;
}

/******************************************************************************
** NAME:  cleanse
** DESCRIPTION: Takes in a vector that is pre-sorted by its first dimension
**				in this case the easting, and if multiple occurences of
**				an easting value appear, the two(or more) points with
**				identical easting values, are again sorted by their second
**				coordinate.
** PARAMETERS:	vector<Location>& v - original vector sorted in the first dimension
**				vector<Location>& v2 - new vector containing all the information of the
**									   first, but sorted in the second dimension as well.
******************************************************************************/
void cleanse(vector<Location>& v)
{
  int i=0;
  int	j=0;
  int size = v.size();
  vector<Location> v2;
  vector<Location> junk;

  quickSort(v, eCompare());
  cout << "Cleaning...";

  while(i < v.size())
  {
    junk.clear();
    junk.push_back(v[i]);
    if(v[i].getEasting() == v[i+1].getEasting())
    {
      while(v[i].getEasting() == v[i+1].getEasting())
      {
        junk.push_back(v[i+1]);
        i++;
      }
      bubbleSort(junk, nCompare());
      for(j=0; j<junk.size(); j++)
      v2.push_back(junk[j]);
    }
    else
    v2.push_back(v[i]);
    i++;
  }
  v2.erase(std::unique(v2.begin(), v2.end()), v2.end());
  v=v2;

  size -= v.size();
  cout << "\nDuplicate Points Removed: " << size << endl;
}

/******************************************************************************
** NAME:  finish
** DESCRIPTION: open new output file for writing.  Write the data, and cleanup and close all
**				open files.
** PARAMETERS:  fstream& infile - reference to input datafile.
**				fstream& outfile - reference to output datafile.
**				char* outname - name of the new output file to be created.
**				vector<Location>& v - vector passed by referece for writing to
**				output, and for cleanup.
******************************************************************************/
void finish(fstream& infile, fstream& outfile, char* outname, vector<Location>& v)
{
  int i=0;

  outfile.setf(ios::fixed);
  outfile.precision(3);
  
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

    for(i=0; i<v.size(); i++)
    outfile << v[i] << endl; outfile.flush();

    cout << "\nData written successfully..." << endl;
  }

  infile.close();
  outfile.close();
  cout << "\nFinished.\n";
}
