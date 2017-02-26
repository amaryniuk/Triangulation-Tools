#include "populateLines.h"

/******************************************************************************
** NAME: 			void displayJobArea(double* x)
** DESCRIPTION:	Just display the spatial extent of the job
** PARAMETERS:		double* - and array of doubles containing key information of the job.
******************************************************************************/
void displayJobArea(double* x)
{
	cout	<< "Job Boundary: Use these coordinates as your guideline.\n"
			<< "Northeast Corner: " << x[1] << ", " << x[3]
			<< "\nSouthwest Corner: " << x[0] << ", " << x[2] << endl;
}

/******************************************************************************
** NAME: 			void getNewLine(string& lineNum, int& stationNum, Location& bol,
**											 Location& eol, double* sE)
** DESCRIPTION:	User inputs the needed information per each line.
** PARAMETERS:		string& - the name of the line
** 					int&	- the station number
** 					Location&, Location& - The BOL and the EOL of the queary line
** 					double* - an array of doubles containing the bounds of the job.
******************************************************************************/
void getNewLine(string& lineNum, int& stationNum, Location& bol, Location& eol, double* sE)
{
	double x=0, y=0;

	cout << "\nEnter line number name : ";
	cin >> lineNum;
	cout << "\nEnter first station number : ";
	cin >> stationNum;

	while(1)
	{
		cout << "\nEnter Coordinates of BOL:\n";
		cout << "Enter BOL Easting: ";
		cin >> x;
		cout << "Enter BOL Northing: ";
		cin >> y;

		if(x>sE[1] || x<sE[0] || y>sE[3] || y<sE[2])		// check if each piece of the user input is outside of
		{																// the bounds defined by double* sE
			cout << "Error: Point is not be in triangulation.\n";
			continue;
		}
		bol.setEasting(x); bol.setNorthing(y);

		cout << "\nEnter Coordinates of EOL:\n";
		cout << "Enter EOL Easting: ";
		cin >> x;
		cout << "Enter EOL Northing: ";
		cin >> y;

		if(x>sE[1] || x<sE[0] || y>sE[3] || y<sE[2])		// again, check the input for bounds errors.
		{
			cout << "Error: Point may not be in triangulation.\n";
			continue;
		}
		eol.setEasting(x); eol.setNorthing(y);
		break;
	}
}

/******************************************************************************
** NAME: 			int pointInTriangle(vector<Triangle>& T, Location& key)
** DESCRIPTION:	A call to pointInTriangle is made to disregard all known mismatched triangles,
** 					once completed, we begin a backward search of the remaining triangles until a
** 					match is found.  A match is true when the queary point lies completly within,
** 					or on the boundary (edge) of a given triangle.
** PARAMETERS:		vector<Trangle>& - reference to the complete vector of triangles.
** 					Location& - the queary point we are searching for.
** RETURN:			int - if we find a match, we return an index into the vector corresponding
** 					to the location of the triangle, otherwise, we return a negative value.
******************************************************************************/
int pointInTriangle(vector<Triangle>& T, Location& key)
{
	int index=0, status=0;
	index = findStartPoint(T, key);
	do												// we want to make sure that we dont underrun
	{												// the boundary of the vector.
		status = T[index].contains(key);
		if(status>0)
			index--;
		else
			break;
	} while(index>=0);
	return index;
}

/******************************************************************************
** NAME:				int findStartPoint(vector<Triangle>& T, double key)
** DESCRIPTION:	We search the vector of triangles for the triangle containing
** 					a queary point represented by the key.  The key is just the easting
** 					value of the queary point.  Since our vector of triangles is sorted
** 					by the west-most coordinates easting value, we do a make-shift binary
** 					search on the vector for easting values that match the key.  In essence, we
** 					disregard all triangles that we know DO NOT containg the queary point.
** 					If a match is found, the index of the triangle is returned.  If no match
** 					is found, the index into the middle (the index that would be returned if
** 					in fact a match did exist) of the vector is returned.
** PARAMETERS:		vector<Triangle>&	-	vector of triangles sorted by increasing order of the
**													westmost point.
** RETURN:			int	-	return an index into the vector that may or may not contain the
**									queary point.  We know for a fact however, that the queary point
**									will be located within a triangle at index i, or at an index less than i.
******************************************************************************/
int findStartPoint(vector<Triangle>& T, Location& key)
{
	int low=0, mid=0, status=0, high=T.size()-1;
	double check=0;

	while(low<=high)								// binary search for the easting value that matches the key.
	{
		mid=(low+high)/2;
		check=T[mid].get1().getEasting();	// Since in all likelyhood, an exact match of the data set
														// is not going to occur, we get as close where the match
		if(key.getEasting()==check)			// would occur, and return that index.
		{
			while(check == T[mid+1].get1().getEasting())
			mid++;
			return mid;
		}
	else if(key.getEasting()<check)
		high=mid-1;
	else
		low=mid+1;
	}
	return mid;
}

/******************************************************************************
** NAME:		double interpolateElevation(Triangle& t, Location& q)
**		Algorithm modified from http://www.geof.ubc.ca/courses/klink/gis.notes/ncgia/u32.html
**		David H. Douglas, University of Ottawa and David M. Mark, State University of New York at Buffalo
**		The equation of a line is y = a + bx where b is the slope.
**		In general, the two lines  y = a1 + b1x  and	y = a2 + b2x  intersect at
**		xi = -(a1 - a2) / (b1 - b2) , yi = a1 + b1xi
**		However, this merely finds the intersection point betwween two lines of infinite length passing
**		through each pair of points.	It is not yet established that the intersection point lies between
**		the pairs, rather than on the imaginary extensions of one or both lines.
**		Let 1 and 2 be lines, with x and y describe coordinates of line 1, and u and v describe
**		the coordinates of line 2.
**		Input x1,y1 & input x2,y2 & input u1,v1 & input u2,v2
**		b1 = (y2-y1)/(x2-x1)	 (A)		b2 = (v2-v1)/(u2-u1)   (B)
**		a1 = y1 - b1 * x1				a2 = v1 - b2 * u1
**		xi = -(a1-a2)/(b1-b2)  (C)		yi = a1 + b2 * xi
**		if (x1-xi)*(xi-x2)>=0  AND	(u1-xi)*(xi-u2)>=0  AND
**			(y1-yi)*(yi-y2)>=0	AND  (v1-yi)*(yi-v2)>=0  then
**		lines cross at xi, yi - else lines do not cross
**		Special Cases : if line 1 is vertical, the instruction laveled (A) will cause an error because
**		of an attempt to divide by zero.	Similarly if line 2 is vertical, line (B) will cause an error.
**		If the two lines are parallel, line (C) will cause an error - because of the nature of our problem,
**		we will not have to consider this.** DESCRIPTION:
** PARAMETERS:	Location& q - A queary point we wish to know the elevation of.
** 				Triangle& t - A triangle containing the queary point q
** RETURN:		double - return the interpolated elevation of the queary point q.
******************************************************************************/
double interpolateElevation(Triangle& t, Location& q)
{
	double a1=0, a2=0, b1=0, b2=0;
	double xi=0, yi=0, zi=0;			// coordinates of the intersection of the two lines

	double d1=0, d2=0;					// distance from the endpoints of one of the intersecting lines,
	double deltaX=0, deltaY=0; 		// to the intersection of the two lines.
	double zp=0;							// The elevation of q	we are trying to find.

	double x1 = q.getEasting(),		  y1 = q.getNorthing();
	double x2 = t.get1().getEasting(), y2 = t.get1().getNorthing(), z1 = t.get1().getElevation();
	double u1 = t.get2().getEasting(), v1 = t.get2().getNorthing(), z2 = t.get2().getElevation();
	double u2 = t.get3().getEasting(), v2 = t.get3().getNorthing(), z3 = t.get3().getElevation();

// Calculate xi, yi : I is a projection of q onto an edge of the triangle t
	findIntersection(x1, y1, x2, y2, u1, v1, u2, v2, xi, yi);

// Now that we have found xi and yi, we can now find zi (interpolated elevation at xi,yi) using pythagoreas
	deltaX = u1-xi;	 deltaY = v1-yi;
	d1 = sqrt (deltaX*deltaX + deltaY*deltaY);

	deltaX = u2-xi;	 deltaY = v2-yi;
	d2 = sqrt (deltaX*deltaX + deltaY*deltaY);

	zi = z2 - ((z2-z3) / (d1+d2)) * d1;

// Calculate zp or the elevation of location q
	deltaX = x1-x2;	 deltaY = y1-y2;
	d1 = sqrt (deltaX*deltaX + deltaY*deltaY);

	deltaX = x1-xi;	 deltaY = y1-yi;
	d2 = sqrt (deltaX*deltaX + deltaY*deltaY);

	zp = z1 - ((z1-zi) / (d1+d2)) * d1;

	q.setElevation(zp);
	return zp;
}

/******************************************************************************
** NAME: 			bool lineTriangleIntersections(Triangle& t, Location& queary, Location& eol, Location& intersection)
** DESCRIPTION:	This function needs quite a bit of explanation to show what I am trying to do.  Imagine for a second
** 					that we have this line starting at BOL, and ending at EOL.	Now this line runs right throught the middle of our
** 					trianglulation, intersecting many many different triangle all over the place (on the edges, on the vertecies,
** 					and sometimes, it has an infinite number of intersections because the line BOL->EOL lies right overtop an edge
** 					of the triangle).  Now what we are trying to accomplish is to find the very first _exit_ point of our line BOL_EOL.
** 					So we are trying to pick out a single intersection when there is possibly an infinite number of them.
** 					This task is made even more difficult due to the poor performance of a previous function pointInTriangle() which
** 					tried to determine the triangle that our insertion point lies in (As a note, if our insertion point happens to be a
** 					vertex of the triangulation, that insertion point does by our definition, lie within all tree triangles).  So,
** 					taking all this into consideration, at the end of this function, we may, or may not have found the correct exit point.
** 					So although I am aware that this is terrible programming practice, These 3(or 4) functions all work hand in hand to
** 					accomplish a single goal.	I will try to explain each step as best I can, but it is important that you keep in mind that
** 					this method also relies on its calling method for a significant amount of error checking.
** PARAMETERS: 	Triangle& - A triangle that has a possibility of containing our exit point.
** 					Location& queary - Our insertion point into the triangle
** 					Location& eol	  - the eol of the line.  we need this to determine our exit point.	i.e. keep your eye on your goal
** 					Location& intersection - A possible intersection or exit point of the triangle
******************************************************************************/
bool lineTriangleIntersections(Triangle& t, Location& queary, Location& eol, Location& intersection)
{
	int status=0;
	double a1=0, a2=0, b1=0, b2=0;
	double d1=0, d2=0;
	double deltaX=0, deltaY=0;

	double u1=0, u2=0, v1=0, v2=0, xi=0, yi=0;								// we have two lines. they are (u1,v1)->(u2,v2)
	double x1 = queary.getEasting(), 	y1 = queary.getNorthing(); 	// and the line					 (x1,y1)->(x2,y2)
	double x2 = eol.getEasting(), 		y2 = eol.getNorthing(); 		// x,y is the line overlaying BOL->EOL, while
																							// u,v is the various lines of the triangle t.
																							// u,v will change depending on which edge we
																							// are currently trying to test.

	bool set=false;
	intersection.setEasting(0); intersection.setNorthing(0);

	if(queary==eol)																	// Check if we are at the end of our line.
	{																						// If so, set the intersection, and return true.
		intersection=eol;
		interpolateElevation(t, intersection);
		return true;
	}

//********************* test edge1 *****************************
	u1 = t.get2().getEasting();	 v1 = t.get2().getNorthing(); 		// set u,v to be the line corresponding to edge 1
	u2 = t.get3().getEasting();	 v2 = t.get3().getNorthing(); 		// that is, from point p2, to point p3.

	if (findIntersection(x1, y1, x2, y2, u1, v1, u2, v2, xi, yi))		// if true, the lines cross at (xi,yi) else,
	{																						// lines do not cross set the intersection
		intersection.setEasting(xi);												// values to the intersection
		intersection.setNorthing(yi);
		if(intersection!=queary) 													// Since we may be testing an incorrect triangle
		{																					// (we do not know for sure) this portion would
			interpolateElevation(t, intersection);								// often come back with the intersection (the exit)
			set=true;																	// of the triangle to be our original insertion point
		}																					// (which is sort of true, since a line through a
	}																						// triangle will have 1, 2, or infinatly many
																							// intersection points.  This test checks the case
																							// where we have two intersection points.

//********************* test edge2 *****************************
	if(!set)
	{
		u1 = t.get1().getEasting(); v1 = t.get1().getNorthing();			// set u,v to be the line corresponding to edge 2
		u2 = t.get3().getEasting(); v2 = t.get3().getNorthing();			// that is, from point p1, to point p3.

		if (findIntersection(x1, y1, x2, y2, u1, v1, u2, v2, xi, yi))	// if true, the lines cross at (xi,yi)
		{																					// else lines do not cross
			intersection.setEasting(xi); 											// set the intersection values to the intersection
			intersection.setNorthing(yi);
			if(intersection!=queary)												// See above.
			{
				interpolateElevation(t, intersection);
				set=true;
			}
		}
	}

//********************* test edge3 *****************************
	if(!set)
	{
		u1 = t.get1().getEasting(); v1 = t.get1().getNorthing();			// set u,v to be the line corresponding to edge 3
		u2 = t.get2().getEasting(); v2 = t.get2().getNorthing();			// that is, from point p2, to point p1.

		if (findIntersection(x1, y1, x2, y2, u1, v1, u2, v2, xi, yi))	// if true, the lines cross at (xi,yi)
		{																					// else lines do not cross
			intersection.setEasting(xi); 											// set the intersection values to the intersection
			intersection.setNorthing(yi);
			if(intersection!=queary)												// See above.
			{
				interpolateElevation(t, intersection);
				set=true;
			}
		}
		else														// We have tested all three edges, and the line x,y does not
			return false; 										// intersect any of them.  Thus, we return false.
	}
//**************************************************************

	status = t.contains(queary);							// Imagine for a second that each of our edges in our
	if(status > 0)												// triangle has an infinite length, that would  mean
		return false;											// that no matter what direction our line BOL_EOL lies,
																	// and in most cases, no matter,  the size, it would
																	// intersect at least one of the edges of our triangle.
																	// To compensate for this, we do a double check to make
																	// sure that our intersection point lies within (or on
																	// an edge) of our triangle (this is a must).

	if(intersection==queary)								// For the life of me, I cannot remember what this test
		return false;											// does, but I am 99% sure that it does something extremly clever.
	else
		return true;
}

/******************************************************************************
** NAME: 			bool findIntersection(double& x1, double& y1, double& x2, double& y2,
** 												 double& u1, double& v1, double& u2, double& v2,
** 												 double& xi, double& yi)
** DESCRIPTION:	We have two lines, (x1,y1),(x2,y2) is the first line, the second line is (u1,v1),(u2,v2).  We need to
** 					determine if the line _segments_ intersect each other, and if so, determine their coordinates.
** PARAMETERS: 	Points (x1,y1) , (x2,y2) , (u1,v1) , (u2,v2)
** 					Intersection point (xi,yi)
******************************************************************************/
bool findIntersection(double& x1, double& y1, double& x2, double& y2,
							 double& u1, double& v1, double& u2, double& v2,
							 double& xi, double& yi)
{
	double a1=0, b1=0, a2=0, b2=0;

	if(x2==x1)
		x2-=LIMIT;
	b1 = (y2-y1) / (x2-x1); 		// slope of queary line
	a1 = y1-b1*x1; 					// y intercept of queary line

	if(u2==u1)
		u2-=LIMIT;						// avoid vertical lines
	b2 = (v2-v1) / (u2-u1); 		// slope of line 2
	a2 = v1-b2*u1; 					// y intercept of line 2

	if(b1==b2)							// avoid parallel lines
		b1-=LIMIT;
	xi = -(a1-a2) / (b1-b2);		// x coordinate of intersection of line1 and line2
	yi = a1 + (b1*xi);				// y coordinate of intersection of line1 and line2

	// Note that all non-parallel lines intersect each other - somewhere - (xi,yi) is
	// that intersection, but we still need to determine if the endpoints defining the
	// line-segments intersect each other.
	// if the line segments intersect return true, else return false
	if ( (x1-xi)*(xi-x2)>=LIMIT	&& (u1-xi)*(xi-u2)>=LIMIT	&&
		(y1-yi)*(yi-y2)>=LIMIT	&& (v1-yi)*(yi-v2)>=LIMIT	)
		return true;
	return false;
}

/******************************************************************************
** NAME: 			double getDistance(Location& p1, Location& p2)
** DESCRIPTION:	Get the slope (3 dimensional) distance between the two points.
** PARAMETERS: 	Location &p1, &p2 - the two points we need the distance between
** RETURN:			double - the distance between the two points.
******************************************************************************/
double getDistance(Location& p1, Location& p2)
{
	double deltaX = p2.getEasting() - p1.getEasting();
	double deltaY = p2.getNorthing() - p1.getNorthing();
	double deltaZ = p2.getElevation() - p1.getElevation();
	double distance = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
	return distance;
}

/******************************************************************************
** NAME: 			void getEndCoord(double& ratio, Location& one, Location& two)
** DESCRIPTION:	Okay, we have come to the situation where have two intersection on either side of our triangle, call
** 					them Location 1 (one) and location two.  Now imagine that there is some distance greater than zero between
** 					one and two.  Now we have this fixed number called an interval.  Now we may only need a portion of the
** 					total distance between point 1 and point 2, to cover the interval.  That portion is described
** 					by the ratio number defined in the parameters.	So in essence, we are just scaling down the coordinates
** 					by a fixed ratio to get than needed middle value (or endpoint)
** PARAMETERS: 	double* ratio - the factor by which we want to scale down the coordinates.
******************************************************************************/
void getEndCoord(double& ratio, Location& one, Location& two)
{
	one.setEasting(one.getEasting() - (one.getEasting()-two.getEasting())*ratio);
	one.setNorthing(one.getNorthing() - (one.getNorthing()-two.getNorthing())*ratio);
	one.setElevation(one.getElevation() - (one.getElevation()-two.getElevation())*ratio);
}

/******************************************************************************
** NAME: 			void populateLines(vector<Triangle>& T, double* spatialExtent, vector<Station>& S)
** DESCRIPTION:	We ask the user for the coordinates of a start and end point which form a line.	Our object is to
** 					'pace out' along the rises and dips of the dtm a fixed number (provided by the user) called the
** 					interval.  As if we are laying a chain along the countours of the dtm.	This in effect chains the
** 					lines, or breaks the line into many stations, with each station having identical chainage to all
** 					others.
** PARAMETERS: 	vector<Triangle>& - Our dtm.	A list of triangles
** 					vector<Station>& - Our new list of stations extracted from the dtm in combination with the
** 											 users input.
** 					double*	- The spatial extent of the job located on the first line of the dtm.
******************************************************************************/
void populateLines(vector<Triangle>& T, double* sE, vector<Station>& S, vector<Queary>& Q)
{
	string lineNum;
	bool endOfLine=false;
	int i=0, index=0, status=0, interval=0, stationNum=0;
	double distanceTotal=0, distanceLocal=0, needed=0;
	Location queary (0,0,0);  Location eol (0,0,0);
	Location check (0,0,0);  Location intersection(0,0,0);
	Station t(lineNum,0,queary);
	int j=0;

//	displayJobArea(spatialExtent);					// Let user know what area (s)he has to work with
	do 														// we should only need to get the size of the
	{															// station interval only once since the only time the
		cout << "\nEnter Station Interval: ";		// interval will change is from reciever lines to source.
		cin >> interval;
		if(interval<=0)
			cout << "Interval must be positive.\n";
	} while (interval<=0);

	for(j=0; j<Q.size(); j++)
	{
		distanceTotal=0;
//		getNewLine(lineNum, stationNum, queary, eol, spatialExtent);
		lineNum=Q[j].getLineName();
		stationNum=Q[j].getLineNum();
		queary=Q[j].getBOL();
		eol=Q[j].getEOL();

		if(queary.getEasting()>sE[1] || queary.getEasting()<sE[0] ||
			queary.getNorthing()>sE[3] || queary.getNorthing()<sE[2])		// check if each piece of the user input is outside of
		{																						// the bounds defined by double* sE
			cout << "Error: Point is not in triangulation.\n";
			continue;
		}
		if(eol.getEasting()>sE[1] || eol.getEasting()<sE[0] ||
			eol.getNorthing()>sE[3] || eol.getNorthing()<sE[2])		// check if each piece of the user input is outside of
		{																						// the bounds defined by double* sE
			cout << "Error: Point is not in triangulation.\n";
			continue;
		}

		index = pointInTriangle(T, queary);								// Get the BOL, (or our new queary point) iterpolate its elevation,
		if(index<0)
		{
			cout << "Fatal Error:  Point not in DTM\n";
			continue;
		}
		interpolateElevation(T[index], queary); 						// and display it to screen for the users benifit, and push it onto
		cout << lineNum << stationNum << "\t" << queary << endl;	// our vector so that it can be written to file at a later time.
		t.setLineName(lineNum); t.setLineNum(stationNum); t.setCoords(queary);
		S.push_back(t);

		endOfLine=false;
		while(1)
		{
			distanceTotal=0;
			do
			{
				index = pointInTriangle(T, queary); 			// Eliminate all triangles we know not to contain the queary point
				interpolateElevation(T[index], queary);		// and begin a seach of the rest for the intersection point in the
				do 														// triangle
				{
					if(!lineTriangleIntersections(T[index], queary, eol, intersection))
					index--;
					else break;
				} while(index>=0);

				distanceLocal = getDistance(queary, intersection); // Compute the distance between our original queary point,
																					// and the point at where the line intersects.

				if(distanceTotal+distanceLocal>=interval) 			// If the distance is greater than that allowed by the interval,
				{																	// we find how much of the local distance (the distance from the queary
					needed = interval-distanceTotal; 					// point, to the intersection of the triangle) we 'need' to make up the
					needed /= distanceLocal;								// total distance.  We then form a ratio of the distance needed over
					getEndCoord(needed, queary, intersection);		// the local distance.
					distanceTotal+=distanceLocal;

					stationNum++;															// Increment the station number, and output the new point to
					cout << lineNum << stationNum << "\t" << queary << endl; // screen, and push onto our vector for file writing.
					t.setLineName(lineNum); t.setLineNum(stationNum); t.setCoords(queary);
					S.push_back(t);
					continue;												// Done, so jump to top of loop to begin a new station.
				}

				else													// If the distance is smaller than needed by the interval, i.e. we have not
				{														// yet reached the next station, we first check to see if we are at the
					if(check==intersection) 					// end of the line.	In this case, We just check to see if the new intersection
					{													// has changed from station to station (which it must have done).  If there is no
						endOfLine=true; 							// change, we set a flag saying we are at end of the line, and break the loop.
						break;
					}
					distanceTotal+=distanceLocal; 			// If we are not at the end of the line, we add the local distance
					queary = intersection;						// to our total distance, and we set our queary point to be our new
					check = intersection;						// current location.  We also set a check flag to determine if we have reached
				}														// the end of our line.

			} while (distanceTotal<=interval);

			// We have just found the latest station.  If we are at the end of the line,
			// we break the loop, otherwise, we continue on to calculate the next station.
			if(endOfLine) break;

		}
	}
}
