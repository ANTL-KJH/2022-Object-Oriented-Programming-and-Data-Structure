/*Student.cpp*/
#include "Student.h"

ostream& operator<< (ostream& fout, Student& st1)
{
	fout << "Student [ st_id:" << setw(6) << right << st1.st_id << ", name: " << left << setw(7) << st1.name << ", gpa: " << setw(4) << st1.gpa << ", regID:" << setw(7) << right << st1.regID << ", nation: " << setw(7) << left << st1.nation << "]";
	return fout;
}

Student::Student()			// default constructor
	:Person()
{
	this->st_id = 0;
	this->gpa = 0.0;
}
Student::Student(int s_id, string n, int reg_ID, string country, double gpa)
	: Person(n, reg_ID, country)
{
	this->st_id = s_id;
	this->gpa = gpa;
}
void Student::getKey(string KeyName, void* pKey)						// getKey
{
	if (KeyName == "ST_ID")
		*(int*)pKey = st_id;
	else if (KeyName == "NAME")
		*(string*)pKey = name;
	else if (KeyName == "GPA")
		*(double*)pKey = gpa;
	else if (KeyName == "REGID")
		*(int*)pKey = regID;
	else if (KeyName == "NATION")
		*(string*)pKey = nation;
	else
		pKey = NULL;
}