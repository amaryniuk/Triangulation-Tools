#ifndef _QUEARY_H_
#define _QUEARY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <iostream>
#include <string>
#include "Location.h"
using namespace std;

class Queary
{
public:
	Queary();
	Queary(string s, int n, Location BOL, Location EOL);
	virtual ~Queary();

	string getLineName () const { return lineName; }
	int getLineNum () 	 const { return lineNum; }
	Location getBOL()		 const { return BOL;; }
	Location getEOL()		 const { return EOL; }

	void setLineName (string s) { lineName=s; }
	void setLineNum (int n) { lineNum=n; }
	void setBOL (Location c) { BOL = c; }
	void setEOL (Location c) { EOL = c; }

	Queary operator=(Queary q);
	friend ostream &operator<<(ostream& out, const Queary& q);

private:
	string lineName;
	int lineNum;
	Location BOL;
	Location EOL;
};

#endif