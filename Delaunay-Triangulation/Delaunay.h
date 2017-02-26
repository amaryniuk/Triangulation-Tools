#ifndef _DELAUNAY_H_
#define _DELAUNAY_H_

#include <vector>
#include <cmath>
#include <stdlib.h>
#include "Location.h"
#include "spatial.h"
#include "Triangle.h"
#include "Graph.h"

void setBoundingTriangle(vector<Location>&v, Location& p1, Location& p2, Location& p3);

void matchTriangles(Triangle& t, Triangle& _t);

void getMidPoint(Location& p1, Location& p2, Location& midPoint);

void findAdjacentVertices(Location& pI, Location& pJ, Location& pK, Location& pL,
									Graph& T, Vertex*& root,
									Triangle& t1, Triangle& t2);

int countNegativeVertices(double p1, double p2, double p3, double p4);

void LegalizeEdge(Location& pR, Location& pI, Location& pJ, Graph& T, Vertex*& root);

void DelaunayTriangulation(vector<Location>& v, Graph& DAG);

#endif
