#ifndef CLASS_STUDENTARRAY_H
#define CLASS_STUDENTARRAY_H
#include "STD_H.h"
#include "Class_Student.h"

class StudentArray
{
	friend ostream& operator<< (ostream&, const StudentArray&);
public:
	StudentArray(int size); // constructor
	StudentArray(const StudentArray& obj);
	~StudentArray();
	int size() const { return num_students; }
	Student& operator[] (int index) const;
	void sortByBirthDate();
	void sortByName();
	void sortByST_ID();
	void sortByGPA();
private:
	Student* students;
	int num_students;
	bool isValidIndex(int index) const;
};
#endif