#ifndef CLASS_PERSON_H
#define CLASS_PERSON_H

#include "STD_H.h"
#include "Class_Date.h"

class Person
{
	friend ostream& operator<< (ostream&, const Person&);
public:
	Person() { birthDate = Date(0, 0, 0); name = ""; }
	Person(string nm, Date bd) { birthDate = bd; name = nm; }
	void setName(string n) { name = n; }
	void setBirthDate(Date bd) { birthDate = bd; }
	string getName() const { return name; }
	Date getBirthDate() const { return birthDate; }
protected:
	Date birthDate;
	string name;
};
#endif