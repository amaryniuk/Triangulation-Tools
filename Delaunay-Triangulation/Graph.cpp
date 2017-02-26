#include "Graph.h"

// Constructor: creates graph with no verticies
Graph::Graph()
{
	first = NULL;
}

// Destructor: deletes the first vertex of the graph, which calls the vertex
// destructor to delete its edges and the other vertexes with their edges
Graph::~Graph()
{
	delete first;
}

// Need to backtrack and find the very first node(vertex) added to the graph.
// This can be called from anywhere, *BUT* it is costly, so it should only be called
// after the first vertex is added to the graph.
Vertex* Graph::getRoot()
{
	Vertex* vPtr = first;
	while(vPtr->getNext() != NULL)
		vPtr = vPtr->getNext();
	return vPtr;
}

// the method returns the pointer to the vertex with data theData
// if such vertex occurs in the graph, otherwise returns NULL
Vertex* Graph::find(Triangle theData)
{
	Vertex* vPtr = first;

	while(vPtr != NULL)
	{
		if(vPtr->getData() == theData) 								// check if the data of the vertex is theData
			return vPtr;
		vPtr = vPtr->getNext();												// go to the next vertex
	}
	return NULL;																		// no match in the loop, so there is no such vertex
}

// This method was spawned in hell.  It takes in a queary point, the root (or bounding triangle/vertex)
// of the graph and two nulled vertex pointer references.  The search of the tree
// is recursive. With each new recursive call to the method, the root is replaced with an appropriate child node which is
// known to contain the query point.  In other words, only an alive vertex can(should) be returned, if a vertex is 'dead',
// an additional recursive call to the method will be envoked with the 'dead' parent as the new root.
int Graph::locateTriangle(Location& pR, Vertex*& root, Vertex*& t1, Vertex*& t2)
{
	int		 status	= 0;
	Vertex*  parent	= root;
	Vertex*  _parent = NULL;											// case: point on edge of triangle
	Edge*	 child	= NULL;

	if(parent != NULL)														// check for empty graph, or undefined reference to parent vertex
	{
		if(parent->isAlive()) 											// only 'alive' vertexes can be returned.  a vertex is 'alive' if and only
		{																						// check if queary point lies within the parent node passed in as 'root'
			status = parent->getData().contains(pR);	// and return -1 if yes, 0 if on edge, or 1 if outside.
			if(status < 0) 														// if it has NO children.	a vertex with children is considered to be dead
			{																					// a 'dead' vertex represents a triangle that used to be in the triangulation
																								// but it no longer exists due to the creation of an 'overlapping' triangle.
				// cout << "\n\nPoint " << pR << " INSIDE TRI " << parent->getData();
				t1 = parent;
				t2 = NULL;
				return -1;
			}
			else if(status == 0)
			{
			// cout << "\n\nPoint " << pR << " ON EDGE "<< parent->getData();
			if(t1 == NULL)
				t1 = parent;
			else
				t2 = parent;
			return 0;
			}
				else
				{
					cout << "\n\nPoint " << pR << " OUTSIDE " << parent->getData();
					t1 = NULL;
					t2 = NULL;
					return 1;
				}
		}
		else // parent->isDead() 											// since the parent is considered to be 'dead', we check each of
		{																							// its children until a child is found which contains the queary point (this
				child = parent->getFirstEdge();						// is because the dead parent has been partitioned into seperate enclosing triangles).
				while(child != NULL)
				{
					parent = child->getEnd(); 										// get the child, set it as parent, if new parent contains the queary point, do a
					status = parent->getData().contains(pR); 			// recursive call to locateTriangle with the new parent set as the root.  if the queary
					if(status > 0)																// point lies outside the bounds of the child triangle, check the next child and repeat
					{																							// until a child is found which does contain the queary point.
						child = child->getNext();										// If it is determined that the queary point lies on an edge of a triangle,
						continue; 																	// recursive calls to locateTriangle must be made for each of the triangles (or vertexes)
					}																							// adjacent to the queary point.
					else if(status < 0)
					{
						return locateTriangle(pR, parent, t1, t2);
					}
					else // else if(status == 0)
					{
						child = child->getNext();							// we have the location of the 'first' triangle which is adjacent to
						while(child != NULL)									// the point - it is stored in parent.  we need to proceed past that vertex (or child rather)
						{																			// and locate the second triangle that is adjacent to the point...  we do this in a similar
								_parent = child->getEnd(); 				// manner as we found the first, but we need only to test for the point being on the edge.
								status = _parent->getData().contains(pR);
								if(status != 0)
								{
									child = child->getNext();
									continue;
								}
								else												// we must to a recursive test on _parent (the second triangle)
								{														// since there may be other triangles within the triangle found to be adjacent to the point.
									locateTriangle(pR, _parent, t1, t2);
									break;
								}
						}    														// again, we must do a recursive test on parent (the first triangle)
						return locateTriangle(pR, parent, t1, t2);
					}
				}
		}
	} 
	cout << "\n\nFatal error encountered: Undefined parent.\n\n";
	exit(1);
}

// the method checks if there is a vertex with data theData in the graph
// if yes, the vertex cannot be added, the method returns 'false'
// otherwise the vertex is added, the method returns 'true'
// NOTE: Linear points will produce a (fucked up) triangle that looks as follows:
// vertex 738.988,-1.#IO,-1.#IO | radius: -1.#IO has no edges
// I dont think you have to check for this though because of the way triangles will be created.
bool Graph::addVertex(Triangle v)
{
	// checking if the vertex is already in the graph, if it is, it cannot be added again
	if(find(v) != NULL)
		return false;

	// allocate memory for new vertex with data theData, make it point to the previous first vertex
	Vertex* newVertex = new Vertex(v, first);
	// make the new vertex the first one in the list of vertexes
	first = newVertex;
	return true;
}

// check if the vertexes with data Begin and End are present in the graph.
// if yes, create an edge from Begin to End, return 'true'
// otherwise return 'false'
bool Graph::addEdge(Triangle begin, Triangle end)
{
	// find the pointer to begin and end vertex
	Vertex* vEnd = find(end);
	Vertex* vBegin = find(begin);

	if(vEnd == NULL) 													// if the vertex is not in the graph, cannot add the edge
		return false;

	if(vBegin == NULL)
		return false;

	if(vBegin == vEnd)												// Graph is acyclic.  No self loops.
		return false;													// Still have to find a way to determine complex cycles.

	vBegin->connectTo(vEnd);										// connect the start vertex to the end one
	return true;
}

// print all vertexes and edges of the graph
void Graph::print(vector<Triangle>& k)
{
	if (first == NULL)
		 cout << "Graph has no Vertices " << endl;
	else
		first->printGraph(k);
}
