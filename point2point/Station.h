#ifndef _STATION_H_
#define _STATION_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <iostream>
#include <string>
#include "Location.h"
using namespace std;

class Station
{
public:
	Station();
	Station(string s, int n, Location c);
	virtual ~Station();

	string getLineName () const { return lineName; }
	int getLineNum () 	 const { return lineNum; }
	Location getCoords()  const { return coords; }

	void setLineName (string s) { lineName=s; }
	void setLineNum (int n) { lineNum=n; }
	void setCoords (Location c) { coords=c; }

	Station operator=(Station p);
	friend ostream &operator<<(ostream& out, const Station& s);

private:
	string lineName;
	int lineNum;
	Location coords;
};

#endif