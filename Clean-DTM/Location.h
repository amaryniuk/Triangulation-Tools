#ifndef _LOCATION_H_
#define _LOCATION_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <iostream>
using namespace std;

/******************************************************************************
 ** NAME:		class Location
 ** ATTRIBUTES:		double	elevation
 **					double	easting
 **					double	northing
 ** METHODS:			double getX () const : Accessor (get) methods for the three values of the point.
 **					void setX (double)	 : Accessor (set) methods for the three values of the point.
 **					operator<<		 Overloaded shift operator<<		: Displays Location to std out.
 **					operator=		 Overloaded assignment operator=	: Assigns all Location attributes of the rhs to lhs.
 **					operator==		 Overloaded comparison operator==	: Return true if rhs equal to lhs.
 ******************************************************************************/
class Location
{
 public:
  Location();
  Location(double _v, double _e, double _n);
  virtual ~Location();

  double getElevation ()	const { return elevation; }
  double getEasting	()	const { return easting;   }
  double getNorthing	()	const { return northing;  }

  void setElevation (double v) { elevation = v; }
  void setEasting	  (double e) { easting   = e; }
  void setNorthing  (double n) { northing  = n; }

  friend ostream &operator<<(ostream& out, const Location& p);
  Location operator=(Location p);
  bool operator==(Location p);
  bool operator!=(Location p);

 private:
  double	elevation;
  double	easting;
  double	northing;
};

#endif
