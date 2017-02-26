#ifndef _EDGE_H_
#define _EDGE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <iostream>
using namespace std;

// forward declaration of the class Vertex needed to reslove
// cyclic dependency between the classes Vertex and Edge
class Vertex;

/******************************************************************************
** NAME: 		class Edge
** ATTRIBUTES: 	Vertex*	: Pointer to the end of the edge.
** 					Edge* : Pointer to the next edge in the list of edges associated with the vertex.
** METHODS: 		Vertex*	getEnd  ()	: Returns the pointer to the end vertex of the edge.
** 					Edge* getNext ()	:	Prints out the data of the end of the edge, then calls the print method
** 												of the next edge on the list (if there is one).
** 					void	print   ()	: Returns the pointer to the next edge on the list
******************************************************************************/
class Edge
{
public:
	Edge(Vertex* vert, Edge* nextEdge);
	~Edge();

	Vertex*	getEnd();
	Edge* getNext();
	void	print();

private:
	Vertex*	end;
	Edge* next;
};

#endif
