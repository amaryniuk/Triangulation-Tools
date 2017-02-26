#ifndef _POPULATE_LINES_
#define _POPULATE_LINES_

#include <vector>
#include "Location.h"
#include "spatial.h"
#include "Graph.h"

void displayJobArea(vector<Location>&, double& minE, double& maxE, double& minN, double& maxN);
void getNewLine(double& BOLEast, double& BOLNorth, double& EOLEast, double& EOLNorth);
void populateLines(vector<Location>&, Graph&);

#endif
