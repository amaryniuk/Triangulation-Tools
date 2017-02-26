#ifndef _GET_INPUT_H_
#define _GET_INPUT_H_

#include <fstream>
#include <vector>
#include <algorithm>

#include "Location.h"
#include "quickSort.h"
#include "comparators.h"
#include "Graph.h"
#include "spatial.h"

enum STRLEN
{
	SHORT_STR=16,
	MED_STR=128,
	LONG_STR=256
};

void startup(char* fname, fstream& infile, int& ecode);

void loadLocations(fstream& infile, vector<Location>& v);

void finish(fstream& infile, fstream& outfile, char* outname, vector<Location>& v, Graph& T);

#endif
