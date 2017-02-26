#ifndef _GET_INPUT_H_
#define _GET_INPUT_H_

#include <fstream>
#include <vector>
#include <algorithm>

#include "Location.h"
#include "Triangle.h"
#include "quickSort.h"
#include "comparators.h"
#include "Station.h"
#include "Queary.h"

enum STRLEN
{
	SHORT_STR=16,
	MED_STR=128,
	LONG_STR=256
};

void startup(char* fname, fstream& infile, fstream& infile2, int& ecode);
void loadLocations(fstream& infile, double* x, vector<Triangle>& T);
void loadQuearyFile(fstream& infile2, vector<Queary>& Q);
void finish(fstream& infile, fstream& infile2, fstream& outfile, char* outname, vector<Station>& S);

#endif
