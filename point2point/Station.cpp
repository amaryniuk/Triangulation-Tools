#include "Station.h"

Station::Station()
{
}

Station::Station(string s, int n, Location c)
{
	lineName=s;
	lineNum=n;
	coords=c;
}

Station::~Station()
{
}

Station Station::operator =(Station p)
{
	lineName = p.getLineName();
	lineNum = p.getLineNum();
	coords = p.getCoords();
	return *this;
}

ostream &operator<<(ostream& out, const Station& s)
{
	return out << s.getLineName() << s.getLineNum() << ',' << s.getCoords();
}
