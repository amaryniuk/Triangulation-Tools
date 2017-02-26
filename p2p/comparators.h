#ifndef _COMPARATORS_H_
#define _COMPARATORS_H_

#include "Location.h"

/******************************************************************************
** NAME: class vCompare
** 		class eCompare
** 		class nCompare
** DESCRIPTION:  Provides a method in which to compare two objects.
******************************************************************************/
class tri1East
{
public:
	bool operator()(const Triangle& a, const Triangle& b)
	{
		return a.get1().getEasting() < b.get1().getEasting();
	}
};

class tri3East
{
public:
	bool operator()(const Triangle& a, const Triangle& b)
	{
		return a.get3().getEasting() < b.get3().getEasting();
	}
};

class tri1North
{
public:
	bool operator()(const Triangle& a, const Triangle& b)
	{
		return a.get1().getNorthing() < b.get1().getNorthing();
	}
};

class tri3North
{
public:
	bool operator()(const Triangle& a, const Triangle& b)
	{
		return a.get3().getNorthing() < b.get3().getNorthing();
	}
};

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
