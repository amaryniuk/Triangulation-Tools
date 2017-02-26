#ifndef _POPULATE_LINES_
#define _POPULATE_LINES_

#include <vector>
#include <cmath>
#include <string>
#include "Location.h"
#include "Triangle.h"
#include "quickSelect.h"
#include "comparators.h"
#include "Station.h"
#include "Queary.h"

#define LIMIT -0.0001
#define RESET 0.001

void displayJobArea(double* x);

void getNewLine(string& lineNum, int& stationNum, Location& bol, Location& eol, double* sE);

int pointInTriangle(vector<Triangle>& T, Location& key);

int findStartPoint(vector<Triangle>& T, Location& key);

double interpolateElevation(Triangle& t, Location& q);

bool lineTriangleIntersections(Triangle& t, Location& queary, Location& eol, Location& intersection);

bool findIntersection(double& x1, double& y1, double& x2, double& y2,
							 double& u1, double& v1, double& u2, double& v2,
							 double& xi, double& yi);

double getDistance(Location& p1, Location& p2);

void getEndCoord(double& ratio, Location& one, Location& two);

void populateLines(vector<Triangle>& T, double* spatialExtent, vector<Station>& S, vector<Queary>& Q);

#endif
