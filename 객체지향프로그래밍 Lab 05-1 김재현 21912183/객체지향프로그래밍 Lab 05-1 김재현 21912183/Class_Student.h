#ifndef CLASS_STUDENT_H
#define CLASS_STUDENT_H
#include "STD_H.h"
#include "Class_Person.h"
#include "Class_Date.h"
#include "MyString.h"

class Date;
class StudentArray;
class Student : public Person
{
	friend class StudentArray;
	friend ostream& operator<< (ostream&, const Student&);
public:
	Student(); // default constructor
	Student(int id);
	Student(int id, string n, Date dob, string dept_n, double gpa);
	int getST_id() const { return st_id; }
	string getDept_name() const { return dept_name; };
	double getGPA() const { return gpa; }
	Date getBirthDate() const { return birthDate; }
	void setST_id(int id) { st_id = id; }
	void setDept_name(string dp_n) { dept_name = dp_n; };
	void setGPA(double g) { gpa = g; }
	const Student& operator=(const Student& right);
	bool operator>(const Student& right);
	bool operator==(const Student& right);
private:
	int st_id;
	string dept_name;
	double gpa;
};
Student genRandStudent(int id);
void genST_ids(int num_students, int* st_ids);

#endif