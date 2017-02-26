#ifndef _GRAPH_H_
#define _GRAPH_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <stdlib.h>
#include "Vertex.h"
#include "Edge.h"
#include "Triangle.h"

/******************************************************************************
** NAME: 			class Graph
** ATTRIBUTES: 	Vertex*	:	Pointer to the first vertex of the graph.
** 									NULL if the graph does not have any vertexes.
** METHODS: 		Vertex* find(Triangle) :	Returns the pointer to the vertex with data theData
** 														if such vertex occurs in the graph, otherwise returns NULL
** 					bool	addVertex(Traingle)	:	Checks if there is a vertex with data theData in the graph.
** 															If yes, the vertex cannot be added, the method returns 'false'
** 															otherwise the vertex is added, the method returns 'true'
** 															NOTE: Linear points will produce a (fucked up) triangle that looks as follows:
** 															vertex 738.988,-1.#IO,-1.#IO | radius: -1.#IO has no edges I dont think
** 															you have to check for this though because of the way triangles will be created.
**
** 					bool	addEdge(Triangle, Triangle)	:	Check if the vertexes with data Begin and End are present
** 																		in the graph. If yes, create an edge from Begin to End, return 'true'
** 																		otherwise return 'false'.
** 					void	print () : Print all vertexes and edges of the graph
** DEPENDENCIES:	class Edge
** 					class Vertex
** 					class Triangle
******************************************************************************/

class Graph
{
public:
	Graph();
	~Graph();

	Vertex* getRoot();
	Vertex* find(Triangle theData);
	Vertex* findChild(Vertex*& parent);

	int	locateTriangle(Location& p, Vertex*& root, Vertex*& t1, Vertex*& t2);
	bool	addVertex(Triangle v);
	bool	addEdge(Triangle begin, Triangle end);
	void	print(vector<Triangle>& k);

private:
	Vertex* first; 		// Stupid name, but pointer to most currently added vertex.
								// Technically, the first vertex in the list.
};

#endif
