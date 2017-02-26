#ifndef _GET_INPUT_H_
#define _GET_INPUT_H_

#include <fstream>
#include <vector>
#include <algorithm>

#include "Location.h"
#include "quickSort.h"
#include "comparators.h"

enum STRLEN
{
  SHORT_STR=16,
  MED_STR=128,
  LONG_STR=256
};

/******************************************************************************
 ** NAME:  startup(char* fname, fstream& infile, int& ecode)
 ** DESCRIPTION:  Prompt user for input data file, open it.  If failure, ecode set
 **				 ecountered open error
 **
 ** PARAMETERS:  char* fname -
 **				fstream& infile -
 **				int& ecode -
 ** RETURN:  void - infile passed by reference - returned open and ready to use
 ******************************************************************************/
void startup(char* fname, fstream& infile, int& ecode);


/******************************************************************************
 ** NAME:  loadLocations(fstream& infile, vector<Location>& v)
 ** DESCRIPTION:  Invoked from main().  Call readLocation() until eof() is reached,
 **				 reading each Location from each line, and loading them into the
 **				 vector passed in by reference.
 ** PARAMETERS:  fstream& infile - reference to open file.
 **				vector<Location>& v - Vector passed by reference. On ititial call of
 **				function, v is empty.  when the function is exited, the vector is loaded
 **				with all the points of the data set pointed to by infile.
 **
 ** RETURN:  void - vector<Location> passed by reference returns vector containing all the
 **				   points of the data set pointed to by infile.
 ******************************************************************************/
void loadLocations(fstream& infile, vector<Location>& v);

void cleanse(vector<Location>&);

/******************************************************************************
 ** NAME:  finish
 ** DESCRIPTION: open new output file for writing.  Write the data, and cleanup and close all
 **				open files.
 **
 ** PARAMETERS:  fstream& infile - reference to input datafile.
 **				fstream& outfile - reference to output datafile.
 **				char* outname - name of the new output file to be created.
 **				vector<Location>& v - vector passed by referece for writing to
 **				output, and for cleanup.
 ******************************************************************************/
void finish(fstream& infile, fstream& outfile, char* outname, vector<Location>& v);

#endif
