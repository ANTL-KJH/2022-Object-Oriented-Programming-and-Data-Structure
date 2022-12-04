/*Student.cpp*/
#include "Student.h"

ostream& operator<< (ostream& fout, Student& st1)			// operation overloading<<
{
	fout << "Student [ st_id:" << setw(6) << right <<st1.st_id << ", name: " << left <<setw(7) << st1.name << ", gpa: " << setw(4) << st1.gpa << ", regID:" << setw(7) << right << st1.regID << ", nation: " << setw(7) << left << st1.nation << "]";
	return fout;					// chained operating
}

Student::Student()					// default constructor
	:Person()
{
	this->st_id = 0;
	this->gpa = 0.0;
}

Student::Student(int s_id, string n, int reg_ID, string country, double gpa)		// constructor
	:Person(n, reg_ID, country)
{
	this->st_id = s_id;
	this->gpa = gpa;
}

void Student::getKey(string keyName, void* pKey)
{
	
}