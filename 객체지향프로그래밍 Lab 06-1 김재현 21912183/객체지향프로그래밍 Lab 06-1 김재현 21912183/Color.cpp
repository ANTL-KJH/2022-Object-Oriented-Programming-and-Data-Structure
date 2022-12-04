/*Color.cpp*/
#include "Color.h"

ostream& fprintRGB(ostream& ostr, const COLORREF color)			// printout color
{
	ostr.fill('0');
	ostr << setw(6) << uppercase << hex << color << dec;
	ostr.fill(' ');
	return ostr;
}