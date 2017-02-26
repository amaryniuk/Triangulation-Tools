#ifndef _COMPARATORS_H_
#define _COMPARATORS_H_

#include "Location.h"

/******************************************************************************
** NAME: class vCompare	eCompare nCompare
** DESCRIPTION:  methods to compare two objects.
******************************************************************************/
class vCompare
{
public:
	bool operator()(const Location& a, const Location& b)
	{
		return a.getElevation() < b.getElevation();
	}
};

class eCompare
{
public:
	bool operator()(const Location& a, const Location& b)
	{
		return a.getEasting() < b.getEasting();
	}
};

class nCompare
{
public:
	bool operator()(const Location& a, const Location& b)
	{
		return a.getNorthing() < b.getNorthing();
	}
};

#endif
