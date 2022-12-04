/* Student.h */
#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"
#include <iomanip>
class Student : public Person
{
	friend ostream& operator<< (ostream&, Student&);
public:
	Student();						// default constructor
	Student(int s_id, string n, int reg_ID, string country, double gpa);		// constructor
	void getKey(string keyName, void* pKey);
	bool operator<(const Student& other) const { return (st_id < other.st_id); }		// operation overloading <
	bool operator<=(const Student& other) const { return (st_id <= other.st_id); }		// operation overloading <=
	bool operator>(const Student& other) const { return (st_id > other.st_id); }		// operation overloading >
	bool operator>=(const Student& other) const { return (st_id >= other.st_id); }		// operation overloading >=
	bool operator==(const Student& other) const { return (st_id == other.st_id); }		// operation overloading ==
private:
	int st_id;
	double gpa;
};
#endif