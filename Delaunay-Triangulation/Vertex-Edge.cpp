#include "Edge.h"
#include "Vertex.h"

// Constructor: creates a vertex with data theData that points to the next
// vertex nextVert and has no outcoming edges
Vertex::Vertex()
{
}

Vertex::Vertex(Triangle theData)
{
	data	= theData;
	next	= NULL;
	edges = NULL;
	alive = true;
}

Vertex::Vertex(Triangle theData, Vertex* nextVert)
{
	data	= theData;
	next	= nextVert;
	edges = NULL;
	alive = true;
}

// Destructor: deletes the outcoming edges (the edge destructor calls
// destructor for the next edge) and calls destructor for the next vertex of the graph
Vertex:: ~Vertex()
{
	delete next;
	delete edges;
}

// Return the Triangle located at the vertex.
Triangle Vertex::getData()
{
	return data;
}

// prints all the edges of the vertex by calling the print method of the first edge
void Vertex::printEdges(vector<Triangle>& k)
{
	if(edges == NULL)
//		if(getData().get1().getElevation()>0
//			&& getData().get2().getElevation()>0
//			&& getData().get3().getElevation()>0)
// 			  cout << getData() << endl;
					k.push_back(getData());


//   cout << "vertex " << getData() << "\t\thas no edges" << endl;
//   else
//   {
// 	  cout << "vertex " << getData() << " \t\thas edges to:\t";
// 	  edges->print();
// 	  cout << endl;
//   }
}

// prints the edges of the vertex, calls the printGraph method for the next vertex
void Vertex::printGraph(vector<Triangle>& k)
{
	printEdges(k);
	if(next != NULL)
		next->printGraph(k);
}

// adds an edge to connect the vertex to the vertex pointed to by Vert
void Vertex::connectTo(Vertex *Vert)
{
	// allocate memory for a new Edge, set its Vertex pointer to point
	// to Vert, and its Edge pointer to point to the rest of edges
	// and make the new edge the first edge of the vertex
	Edge *newEdge = new Edge(Vert, edges);
	edges = newEdge;
}

// returns the pointer to the next vertex in the graph
Vertex *Vertex::getNext()
{
	return next;
}

// returns the pointer to the first outcoming edge of the vertex
Edge *Vertex::getFirstEdge()
{
	return edges;
}

// methods of class Edge
// Constructor: sets the two fields to the two given values
Edge::Edge(Vertex *vert, Edge *nextEdge)
{
	end  = vert;
	next = nextEdge;
}

// Destructor: calls the destructor for the next edge on the list
Edge::~Edge()
{
	delete next;
}

// returns the pointer to the end vertex of the edge
Vertex *Edge::getEnd()
{
	return end;
}

// prints out the data of the end of the edge, then calls the print method
// of the next edge on the list (if there is one)
void Edge::print()
{
	cout << end->getData() << " \t ";
	if(next != NULL)
		next->print();
}

// returns the pointer to the next edge on the list
Edge *Edge::getNext()
{
	return next;
}
