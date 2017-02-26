#ifndef _VERTEX_H_
#define _VERTEX_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Edge.h"
#include "Triangle.h"
#include <vector>

/******************************************************************************
** NAME: 			class Vertex
** ATTRIBUTES: 	Trangle	:	The data to be stored at each vertex is a Triangle.
** 					Edge* :	Pointer to the list of outcoming edges of the vertex.
** 					Vertex*	:	Pointer to the next vertex in the graph.
** 					bool	:
** METHODS: 		Triangle getData		()		:	Return the Triangle located at the vertex.
** 					void printEdges		()		:	Print all the edges of the vertex by calling the print method
** 															of the first edge as described in Edge.h.
** 					void pringGraph		()		:	Prints all vertexes and edges of the graph, calls the printGraph method for the next vertex.
** 					void connectTo (Vertex*)	:	Adds an edge which connects the vertex to the vertex pointed to by Vert.
** 					Vertex* getNext		()		:	Returns a pointer to the next vertex in the graph.
** 					Edge* getFirstEdge	()		:	Returns a pointer to the first outcoming edge of the vertex.
** DEPENDENCIES:	class Edge
** 					class Triangle
******************************************************************************/
class Vertex
{
public:
	Vertex();
	Vertex(Triangle theData);
	Vertex(Triangle theData, Vertex* nextVert);
	~Vertex();

	Triangle getData();
	void printEdges(vector<Triangle>& k);
	void printGraph(vector<Triangle>& k);
	void connectTo(Vertex* Vert);
	bool isAlive () { return alive; }
	void kill () { alive = false; }

	Vertex*	getNext();
	Edge* 	getFirstEdge();

private:
	Triangle data;
	Edge* 	edges;
	Vertex*	next;
	bool		alive;
};

#endif
