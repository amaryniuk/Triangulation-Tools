#ifndef _SPATIAL_H_
#define _SPATIAL_H_

#include <vector>
#include "comparators.h"
#include "quickSelect.h"

double greatestSpatialExtent(vector<Location>& v, double& minE, double& maxE,
																  double& minN, double& maxN);

// void vExtent(vector<Location>& v, double& minV, double& maxV);
void eExtent(vector<Location>& v, double& minE, double& maxE);
void nExtent(vector<Location>& v, double& minN, double& maxN);

long medV(vector<Location>& v);
long medE(vector<Location>& v);
long medN(vector<Location>& v);

#endif
