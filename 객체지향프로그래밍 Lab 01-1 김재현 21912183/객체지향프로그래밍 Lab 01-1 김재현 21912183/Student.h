/*Student.h*/
#ifndef StudentH
#define StudentH
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
typedef struct
{
	int st_id;
	char name[16];
	char dept[16];
	int grade;
	double gpa;
} Student;
void initStudents(Student students[], int st_ids[], int num_students);
void fprintStudent(ostream& fout, Student* pSt);
void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last);
void selectionSortStudentsBy_ID(Student students[], int num_students);
void selectionSortStudentsBy_GPA(Student students[], int num_students);
Student* binarySearchStudentByID(Student* students, int num_students, int st_id);
void fprintStudents(ostream& fout, Student* students, int num_students);
void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last);
#endif