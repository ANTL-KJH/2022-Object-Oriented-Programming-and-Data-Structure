/*Person.cpp*/
#include "Person.h"

ostream& operator<< (ostream& fout, const Person& p)			// operation overloading
{
	fout << "Person: name(" << p.name << "), regID(" << p.regID << "), nation(" << p.nation << ")" << endl;
	return fout;
}