/*Class_Person.cpp*/
#include "Class_Person.h"

ostream& operator<<(ostream& fout, const Person& p1)
{
	fout << "Name : " << setw(8) << p1.name << ", BirthDate : " << p1.birthDate;		// printout


	return fout;											// chained operationg
}