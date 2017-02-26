#include "Queary.h"

Queary::Queary()
{
}

Queary::Queary(string s, int n, Location _BOL, Location _EOL)
{
	lineName=s;
	lineNum=n;
	BOL=_BOL;
	EOL=_EOL;
}

Queary::~Queary()
{
}

Queary Queary::operator =(Queary q)
{
	lineName = q.getLineName();
	lineNum = q.getLineNum();
	BOL = q.getBOL();
	EOL = q.getEOL();
	return *this;
}

ostream &operator<<(ostream& out, const Queary& q)
{
	return out << q.getLineName() << q.getLineNum() << ',' << q.getBOL() << q.getEOL();
}