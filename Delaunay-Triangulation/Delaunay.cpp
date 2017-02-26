#include "Delaunay.h"

// A more in depth discussion of Delaunay Triangulation can be found in the book Berg et. al:
// Computational Geometry - Algorithms and Applications from Springer Verlag. The algorithm described
// above is inspired from that book.

/******************************************************************************
** NAME:        void setBoundingTriangle(vector<Location>&, Location&, Location&, Location&)
** DESCRIPTION:	Create a bounding Triangle which encompasses the Point set.  The three
** 	       	points of the triangle must be choosen such that their presence does not
** 		influence the delaunay triangulation of the point set P.
** PARAMETERS:
** 		Point p1 := (3M, 0) where M is the maximum absolute value of any coordinate of a point in P
** 		Point p2 := (0, 3M)	where M is the maximum absolute value of any coordinate of a point in P
** 		Point p3 := (-3M, -3M)	where M is the maximum absolute value of any coordinate of a point in P
** DEPENDENCIES:
** 		double greatestSpatialExtent(vector<Location>&, Location&, Location&, Location&, Location&)
** RETURN:	void - Points P1, P2, P3 passed by reference. No change to vector except ordering.
******************************************************************************/
void setBoundingTriangle(vector<Location>& v, Location& p1, Location& p2, Location& p3)
{
  const int C=4;

  double maxDimension;  /* From theorhetical center point of the point set P, represents the greatest maximum extent from the center,
     the edge of the Point set (ie, the job) ie. it is the maximum absolute value of any coordinate of a point in P */

  double meanE, meanN; 						// The theoretical center point of the point set can be expressed as an Easting<-meanE and a Northing<-meanN
  double minE, maxE, minN, maxN;	// Maximum(al) spatial extent of the point set in all four dimensions.


  maxDimension = greatestSpatialExtent(v, minE, maxE, minN, maxN);
                                          // and maxDimension returned by function
                                          // minE -> maxN all passed by reference and set within function call
  meanE = (maxE - minE) / 2 + minE;	      // Theoretical central easting value of the point set (or dimension 1)
  meanN = (maxN - minN) / 2 + minN;		    // Theoretical central northing value of the point set (or dimension 2)

                                                                // For p1, p2, p3 : All elevations have no real value -	we set to -1 to
                                                                // distingush between the interior point set, and the bounding points.
                                                                // Note that the lowest elevation in Canada is 0m
  p1.setElevation(-1); 						                              // Point p1 := (CM, 0) where M is the maximum absolute value of any
  p1.setEasting(meanE + C*maxDimension);                        // coordinate of a point in P, and 0 represents no change in the
  p1.setNorthing(meanN);				      	                        // mean value of the 2nd dimension.
  p2.setElevation(-2); 						                              // Point p2 := (0, CM)	where M is the maximum absolute value of any
  p2.setEasting(meanE);						                              // coordinate of a point in P, and 0 represents no change in the
  p2.setNorthing(meanN + C*maxDimension);                       // mean value of the 2nd dimension.
  p3.setElevation(-3); 						                              // Point p3 := (-CM, -CM) where M is the maximum absolute value of any
  p3.setEasting(meanE - C*maxDimension);                        // coordinate of a point in P
  p3.setNorthing(meanN - C*maxDimension);
}

/******************************************************************************
** NAME: 	void matchTriangles(Triangle& t1, Triangle& t2)
** DESCRIPTION:	If a query point is inserted into the triangulation and is determined to be
** 	     	adjacent to two of the triangles, ie, on an edge of a triangle, we need to determine
** 		which edge of each triangle the point lies on.	If you were to draw two triangles
** 		adjacent to each other (meaning, they share an edge) you would note that they
** 		share two vertecies, and the other two verticies are not shared.	By finding which of the vertices are
** 		shared by the two triangles, we find which edge of the possible 5 edges in the polygon
** 		is shared.  Once found we perform a rotation on each of the triangles to ensure that the
** 		two vertices that are not on the shared edge, are in the 'first position' of the triangle.
**
** 				  shared vertex ------>
** 				                       /|\
** 						                  / | \
** 		 vertex not shared ----> /	|  \ <---- vertex not shared (put in first position)
** 		 (put in first position) \	|  /
** 		      			              \ | /
** 					                     \|/ <------ shared vertex
** PARAMETERS:  Triangle& t, _t - Triangles adjacent to queary point.
** RETURN:		 void
******************************************************************************/
void matchTriangles(Triangle& t, Triangle& _t)
{
  Location  key, o1, o2;
  Location  p1 =  t.get1(),
    p2 =  t.get2(),
    p3 =  t.get3();
  Location _p1 = _t.get1(),
    _p2 = _t.get2(),
    _p3 = _t.get3();

  if(p1!=_p1 && p1!=_p2 && p1!=_p3)		// If first point in first triangle != any of the three
    {						                      // points in the second triangle.
      key = p1;				                // Set key to be that point, and o1, o2 to be remaining two points.
      o1  = p2;
      o2  = p3;
    }
  else if(p2!=_p1 && p2!=_p2 && p2!=_p3)        // If second point in first triangle != any of the three
    {					      	                          // points in the second triangle.
      key = p2;	       				                  // Set key to be that point, and o1, o2 to be remaining two points.
      o1  = p1;
      o2  = p3;
    }
  else					        // If third point in first triangle != any of the three
    {						        // points in the second triangle.
      key = p3;					// Set key to be that point, and o1, o2 to be remaining two points.
      o1  = p1;
      o2  = p2;
    }
  Triangle temp1(key, o1, o2);			// Create new triangle with key as first point in the triangle
  t = temp1;				                // and let t <-- this new triangle

  if(_p1!=p1 && _p1!=p2 && _p1!=p3)		// If first point in second triangle != any of the three
    {					                        // points in the first triangle.
      key = _p1;				              // Set key to be that point, and o1, o2 to be remaining two points.
      o1  = _p2;
      o2  = _p3;
    }
  else if(_p2!=p1 && _p2!=p2 && _p2!=p3)         // If first point in second triangle != any of the three
    {						                                 // points in the first triangle.
      key = _p2;			                           // Set key to be that point, and o1, o2 to be remaining two points.
      o1  = _p1;
      o2  = _p3;
    }
  else						    // If first point in second triangle != any of the three
    {						      // points in the first triangle.
      key = _p3;			// Set key to be that point, and o1, o2 to be remaining two points.
      o1  = _p1;
      o2  = _p2;
    }
  Triangle temp2(key, o1, o2);			   // Create new triangle with key as first point in the triangle
  _t = temp2; 					               // and let _t <-- this new triangle
}

/******************************************************************************
** NAME: 	void getMidPoint(Location& p1, Location& p2, Location& midPoint)
** DESCRIPTION:	Take in two points (the endpoints of a line) and find
** 		the midpoint along that line.  You don't necessarily need to find the exact midpoint,
** 		just any point on the line.  However, finding the midpoint seems to be the easiest.
** PARAMETERS: 	Location &p1, &p2 - The endpoints
** 	        Location &midPoint - The midpoint.
******************************************************************************/
void getMidPoint(Location& p1, Location& p2, Location& midPoint)
{
	midPoint.setElevation ((p1.getElevation() + p2.getElevation()) / 2 );
	midPoint.setEasting	 ((p1.getEasting()	+ p2.getEasting()  ) / 2 );
	midPoint.setNorthing  ((p1.getNorthing()	+ p2.getNorthing() ) / 2 );
}

/******************************************************************************
** NAME: 	void findAdjacentVertices(Location& pI, Location& pJ, Location& pK, Location& pL, Graph& T, Vertex*& root)
** DESCRIPTION:	If we test an edge for legalization (determine if an edge is legal) we need to find the
** 					edge that would be created if the tested edge is illegal.  This 'created' edge would intersect the
** 					tested edge, and would have verticies adjacent to (and not equal to) those verticies of the
** 					tested edge.  To find these adjacent verticies - we utilize the locateTriangle method by creating a new
** 					point that lies somewhere on the tested edge.  An easy way to do this is to just find the midpoint of
** 					the tested edge.	Since we know that the midpoint lies exactly on the tested edge, we know that the midpoint
** 					has two triangles adjacent to it.  We plug this point into our locateTriangle method which returns
** 					both triangles if a point is determined to be on an edge.
** DEPENDENCIES:	getMidpoint()
** 					locateTriangle()
** 					matchTriangles()
** PARAMETERS: 	Location &pI, &pJ : The verticies of the 'tested' edge
** 					Locaiton &pK, &pL : The verticies of the 'created' edge
** 					Graph&				: Reference to the directed graph
** 					Vertex& root:		: The root of the directed graph
** 					Vertex &t1, &t2	: Pointers to the triangles returned by locateTriangle.
******************************************************************************/
void findAdjacentVertices(Location& pI, Location& pJ, Location& pK, Location& pL,
								  Graph& T, Vertex*& root,
								  Vertex*& t1, Vertex*& t2)
{
		Location midPoint;
		getMidPoint(pI, pJ, midPoint);

		int status = T.locateTriangle(midPoint, root, t1, t2);

		if(!t1 || !t2)
		{
			cout << "\nFatal error encountered: Unable to Locate Triangles.\n\n";
			exit(-1);
		}

		Triangle _t1 = t1->getData();
		Triangle _t2 = t2->getData();
		matchTriangles(_t1, _t2);

		pK = _t1.get1();
		pL = _t2.get1();
}

/******************************************************************************
** NAME: 	int countNegativeVertices(double p1, double p2, double p3, double p4)
** DESCRIPTION:	it is important to know the number of negative verticies (or the number
** 					of special points) in the legalization. By positive we mean the vertex is (not a special)
** 					or (not a bounding) vertex and naturally negative is just the opposite, the vertex is a
** 					(special) or (bounding) vertex.
** PARAMETERS: 	double p1, p2, p3, p4 : The elevations of the four verticies ( or of each point )
** 					show if a point is special, or a bounding point.
** RETURN:		 integer : the number of negative verticies.
******************************************************************************/
int countNegativeVertices(double p1, double p2, double p3, double p4)
{
	int count = 0;
	if(p1<0) count++;
	if(p2<0) count++;
	if(p3<0) count++;
	if(p4<0) count++;
	return count;
}

/******************************************************************************
** NAME: 	void LegalizeEdge(Location& pR, Location& pI, Location& pJ, Graph& T, Vertex*& root)
** DESCRIPTION:	A triangulation is a Delaunay triangulation if all its edges are legal.  We therefore
** 					flip illegal edges until the triangulation is legal again.	Observe that an edge pIpJ
** 					that was legal before can only become illegal if one of the triangles incident to it has been changed.
** 					So only the edges of the new triangles need to be checked.	LegalizeEdge() tests, and possibly
** 					flips an edge.  If LegalizeEdge() flips and edge, other edges may become illegal.  LegalizeEdge() calls
** 					itself recursively with such potentially ileegal edges.	There are some complications however because
** 					of the presence of the special points p_-1, p_-2, p_-3.	The different possible cases are described
** 					in further detail below where each case is implemented.
** PARAMETERS: 	Graph& T - A set T of n points in the plane.
** 					Vertex*& root - The very first node(vertex) or triangle added to the graph T.
** 					Location& pR - The point being inserted.
** 					Location &pI, &pJ - (Also expressed as pIpJ) is the edge of T that may need to be flipped.
** 												Each edge of the bounding triangle of the queary point pR is checked
** 												for a legalEdge, and flipped if neccessary.
******************************************************************************/
void LegalizeEdge(Location& pR, Location& pI, Location& pJ, Graph& T, Vertex*& root)
{
	int  iL=0, numNegVert=0;
	double lowIndexIJ=0, lowIndexKL=0;
	bool legalEdge=true;

// We stated earlier that LegalizeEdge() tests, and possibly flips an edge.  We also stated that some
// complications arise because of the existance of the special bounding points p_-1 p_-2 and p_-3.
// The five cases below (marked case(i) through case(v)) are meant to handle those complications, and are
// described in further detail within each case as needed.

	if(pI.getElevation()<0 && pJ.getElevation()<0)		// case (i): both I and J are negative.
		legalEdge=true;                                 // In this case we decide that pIpJ is legal,
		                                                // because we must keep the edges of the large triangle p_-1 , p_-2 , p_-3

	// For the other cases, we let pK and pL be the other two vertices of the triangles incident to pIpJ
	else
	{
		Location pK, pL;
		Vertex* t1=NULL; Vertex* t2=NULL;

		findAdjacentVertices(pI, pJ, pK, pL, T, root, t1, t2);		// The edge to be legalized can be represented by the points stored in pI and pJ
																						                  // and the two points perpendicular (adjacent) to that edge are found in pK and pL.
																						                  // If pIpJ is illegal, pIpJ will be replace by the edge pkpL.

		numNegVert = countNegativeVertices( pI.getElevation() ,		// For the remaining cases, it is important to know
														pJ.getElevation() ,		// the number of negative verticies (or the number
														pK.getElevation() ,		// of special points) in the legalization.
														pL.getElevation() ); 	// By positive I mean (not special) or (not bounding) vertex.
																						// and naturally negative := (special) or (bounding) vertex.

		if(numNegVert == 0)										// case (ii): the indicies I, J, K, L are all positive.
			// This is the normal case; none of the points involved in the test is a special point.
			// Hence, pIpJ is illegal if and only if pL lies inside the circle defined by pI, pJ, and pK.
			// So we set legalEdge to false, and let the test be done below.
			legalEdge=false;

		else if(numNegVert == 1)								// case (iii): exactly one of the indices I, J, K, L is negative.
			// We don't want a special point to destroy any Delaunay edges betwwen points in P.
			// Hence, if I or J is negative (that is, pI or pJ is a special point) then we
			// decide that pIpJ is illegal so that it will be replaced by pKpL; otherwise we
			// decide that pIpJ is legal.
			(pI.getElevation()<0 || pJ.getElevation()<0) ? legalEdge=false : legalEdge=true;

		else if(numNegVert == 2)								// case (iv): exactly two of the indices I, J, K, L are negative.
		{
			// Now one of I, J and one of K, L must be negative; we cannot have that both K, L are
			// negative and the case that both I, J are negative as was in case (i) above.
			// If the negative index of I, J is smaller than the negative index of K, L then we decide that
			// pIpJ is legal, and otherwise we decide it is illegal
			(pI.getElevation()<0) ? lowIndexIJ=pI.getElevation() : lowIndexIJ=pJ.getElevation();
			(pK.getElevation()<0) ? lowIndexKL=pK.getElevation() : lowIndexKL=pL.getElevation();

			(lowIndexIJ > lowIndexKL) ? legalEdge=true : legalEdge=false;

		} // end else

		else if(numNegVert == 3)								// case (v): exactly three of the indices I, J, K, L are negative.
		{
			// This cannot occur:  I and J cannot both be negative -- that was case (i) -- and K and L
			// cannot both be negative because one of pK, pL must be the point pR that we just inserted.
			cout << "\n\nFatal error encountered:  Error Building Triangulation.\n\n";
			exit(1);
		}

// We need to flip illegal edges until the triangulation is legal again.	Observe that an edge pIpJ
// that was legal before can only become illegal if one of the triangles incident to it has been changed.
// So only the edges of the new triangles need to be checked.	We stated earlier that LegalizeEdge() tests,
// and possibly flips an edge.  This portion of the code does the flip once the edge has been checked, and is
// determined to be 'illegal'.  If LegalizeEdge() flips and edge, other edges may become illegal.
// LegalizeEdge() calls itself recursively with such potentially ileegal edges.

		if(!legalEdge) 											      // if pIpJ is illegal : Flip pIpJ (Replace pIpJ with pRpK)
		{
			if(pR == pK)											      // We ensure that we the edge we want to insert is pRpK
				pK = pL;

			Triangle isLegal(pI, pJ, pK); 					// The case(s) above have determined the edge to be an illegal edge, however,
			iL = isLegal.circleContains(pR); 				// we still need to do the 'circle test' to double check that the edge is
																		          // in fact an illegal edge.  We make a new (temporary) triangle, and test the
			if(iL < 0)												      // fourth point to see if the new edge is 'better' than the one that already exists.
			{															          // If and only if it is 'better', do we replace it.

				Triangle new1( pI, pR, pK );					// Add two new triangles to the directed graph
				Triangle new2( pJ, pR, pK );					// and create pointers (graph edges) from the original two
																		// triangles incident to edge pIpJ to the two new triangles which
				T.addVertex(new1);								// are incident to edge pkpR
				T.addVertex(new2);

				T.addEdge(t1->getData(), new1);
				T.addEdge(t1->getData(), new2);
				T.addEdge(t2->getData(), new1);
				T.addEdge(t2->getData(), new2);

				t1->kill(); 										// Set pIpJpK and pIpJpR to dead since they have been replaced by the
				t2->kill(); 										// triangles pIpRpK and pJpRpK

				LegalizeEdge(pR, pI, pK, T, root);			// If legalizeEdge flips an edge, other edges may become illegal.
				LegalizeEdge(pR, pK, pJ, T, root);			// Therefore, legalizeEdge callis itself recursivly with such potential
			}															            // illegal edges.
		}
	}
}

/******************************************************************************
** NAME: 	void DelaunayTriangulation(vector<Location>& v, Graph& T)
** DESCRIPTION:	We start with a large triangle (a bounding triangle) call it p_-1, p_-2, p_-3. This bounding triangle
** 					contains the point set P.	This means we are now comptng a Delaunay triangulation of P union Omega instead
** 					of P, where Omega := { p_-1, p_-2, p_-3 }. Later we want to obtain the Delaunay triangulation of P by
** 					discarding p_-1, p_-2, p_-3.	For this to work we have to choose these points far enough away so that they
** 					dont destroy any triangles in the Delaunay triangulation of P.  In particular, we must ensure they do not lie
** 					in any circle defined by three points in P.
** 					The algorithm is randomized incremental, so it adds the points in random order and it maintains a Delaunay
** 					triangulation of the current point set.  Consider the addition of a point pR.  We first find the triangle of
** 					the current triangulation that contains pR -- and we add edges from pR to the vertices of this triangle.
** 					If pR happens to fall on an edge e of the triangulatin, we have to ad edges from pR to the opposite vertices
** 					in the triangles sharing e.  We now have a triangulation again, but not necessarily a Delaunay triangulation.
** 					This is because the addition of pR can make some of the existing edges illegal.	To remedy this, we call a
** 					procedure LegalizeEdge with each potentially illegal edge.	This procedure replaces illegal edges by legal
** 					ones through edge flips.
** PARAMETERS: 	vector<Location>& v : The point set to be triangulated.
** 					Graph& T : The Graph structure which contains the triangulation.
******************************************************************************/
void DelaunayTriangulation(vector<Location>& v, Graph& T)
{
	int pR=0, status=0, count=1;
	Vertex* root;
	Location P_neg1 , P_neg2, P_neg3;					      // Let p_neg1, p_neg2, p_neg3 be a suitable set of three points
	setBoundingTriangle(v, P_neg1, P_neg2, P_neg3); // such that P is contained in the traingle p_neg1, p_neg2, p_neg3.

	Triangle bound(P_neg1, P_neg2, P_neg3);			// Initialize T as the triangulation consisting of the single triangle
	T.addVertex(bound);										      // with vertexes at points p_neg1, p_neg2, and p_neg3.
	root = T.getRoot();										      // Set the root to be the very first node(vertex) added to the graph.
  // cout << "BOUND:  " << bound << endl;

	Vertex* t1 = NULL; Vertex* t2 = NULL;
	cout << "Building Delaunay Triangulation...";

	for(pR=0; pR<v.size(); pR++)									// Insert each point in set P into triangulation T
	{
		cout << count++ << ' ';
		t1 = NULL; t2 = NULL;
		status = T.locateTriangle(v[pR], root, t1, t2); 	// Find a triangle pIpJpK containing pR.

		if(status < 0) 												// if(Pr lies in the interior of the triangle pIpJpK)
		{																	    // Add edges from pR to the three vertices of pIpJpK thereby
			Triangle _t1 = t1->getData(); 			// splitting pIpJpK into tree triangles

			Triangle new1( v[pR] , _t1.get1() , _t1.get2() );
			Triangle new2( v[pR] , _t1.get2() , _t1.get3() );
			Triangle new3( v[pR] , _t1.get3() , _t1.get1() );

			T.addVertex(new1);										// Add the three new triangles to the directed graph
			T.addVertex(new2);										// and create pointers (graph edges) from the original
			T.addVertex(new3);										// triangle pIpJpK to the three new triangles

			T.addEdge(t1->getData(), new1);
			T.addEdge(t1->getData(), new2);
			T.addEdge(t1->getData(), new3);

			t1->kill(); 												// Set pIpJpK to dead since it has outcoming triangles (triangles within)

			Location t1p1 = _t1.get1(); Location t1p2 = _t1.get2(); Location t1p3 = _t1.get3();

			LegalizeEdge(v[pR], t1p1, t1p2, T, root);
			LegalizeEdge(v[pR], t1p1, t1p3, T, root);
			LegalizeEdge(v[pR], t1p2, t1p3, T, root);
		}

		else if(status == 0) 											// else if pR lies on an edge of pIpJpK, say the edge pIpJ
		{																		      // Add edges from pR to pK and to the third vertec pL of the other
			Triangle _t1 = t1->getData(); 					// triangle that is incident to pIpJ, thereby splitting the two
			Triangle _t2 = t2->getData(); 					// triangles incident to pIpJ into four triangles.
			matchTriangles(_t1, _t2);

			Triangle new1( v[pR] , _t1.get1() , _t1.get2() );
			Triangle new2( v[pR] , _t1.get1() , _t1.get3() );
			Triangle new3( v[pR] , _t2.get1() , _t2.get2() );
			Triangle new4( v[pR] , _t2.get1() , _t2.get3() );

			T.addVertex(new1);										// Add the four new triangles to the directed graph
			T.addVertex(new2);										// and create pointers (graph edges) from the two original
			T.addVertex(new3);										// triangle pIpJpK and pIpJpL to the four new triangles (two each
			T.addVertex(new4);										// determined by which of triangle the two new triangles are within

			T.addEdge(t1->getData(), new1);
			T.addEdge(t1->getData(), new2);
			T.addEdge(t2->getData(), new3);
			T.addEdge(t2->getData(), new4);

			t1->kill(); 												// Set pIpJpK and pIpJpL to dead since each has
			t2->kill(); 												// outcoming triangles (triangles within)

			Location t1p1 = _t1.get1(); Location t1p2 = _t1.get2(); Location t1p3 = _t1.get3();
			Location t2p1 = _t2.get1(); Location t2p2 = _t2.get2(); Location t2p3 = _t2.get3();

			LegalizeEdge(v[pR], t1p1, t1p2, T, root);
			LegalizeEdge(v[pR], t1p1, t1p3, T, root);
			LegalizeEdge(v[pR], t2p1, t2p2, T, root);
			LegalizeEdge(v[pR], t2p1, t2p3, T, root);
		}
		else
		{
			cout << "\n\nFatal error encountered:  Error Building Triangulation.\n";
			exit(1);
		}
	}
	cout << "\n\nDelaunay Triangulation built successfully.\n";
}
