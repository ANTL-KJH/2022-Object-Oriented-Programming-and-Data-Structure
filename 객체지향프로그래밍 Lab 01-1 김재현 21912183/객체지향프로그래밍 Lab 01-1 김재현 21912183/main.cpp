/*
* ������Ʈ�� : "��ü�������α׷��� Lab 01-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* -32,767���� ū ������ �迭�� �����ϰ� �л� ����ü�� ����ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.08.31
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������		����			����		��������
* JH KIM			2022.08.31	v1.0	���� �ۼ�
* JH KIM			2022.09.01	v1.1	�Լ� �ۼ�
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "genBigRandArray.h"
#include "Student.h"
using namespace std;
#define NUM_STUDENTS 5000
#define NUM_SEARCH 5
#define NUM_FIRST_LAST_BLOCK 100


int main(void)
{
	ofstream fout;		// output file
	int* student_ids;
	Student* students, * pSt;
	int student_search[NUM_SEARCH] = { 1, 123, 999, 2500, 4999 };
	fout.open("output.txt");		// file open
	if (fout.fail())				// file open�� �����Ѱ�� exit
	{
		cout << "Error in opening output.txt" << endl;
		exit;
	}
	students = (Student*)calloc(NUM_STUDENTS, sizeof(Student));		// Dynamic Memory Allocation
	student_ids = genBigRandArray(NUM_STUDENTS, 0);					// Bigrandom�� �����Ͽ� student_ids�� �Է�
	initStudents(students, student_ids, NUM_STUDENTS);				// initialize Student Structure array

	fout << endl << endl;
	fout << "Initialized array of students : " << endl;
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);	// BigRand�� ������ �л��� id�� �յ� 100���� ������ �����Ͽ� ���
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);									// id�� �������� selection sorting
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Sorting array of students by (decreasing order of GPA, increasing order of ID) : " << endl;
	selectionSortStudentsBy_GPA(students, NUM_STUDENTS);								// GPA �������� ����, GPA�� ���� �� id �������� ����
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);									// id�� �������� selection sorting
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Searching student with student_ID : " << endl;
	for (int i = 0; i < NUM_SEARCH; i++)
	{
		pSt = binarySearchStudentByID(students, NUM_STUDENTS, student_search[i]);		// ID�� �������� ����Ž��
		fout << "Student search by ID (" << setw(4) << student_search[i] << ") : ";
		if (pSt != NULL)
			fprintStudent(fout, pSt);
		else
			fout << "NULL - student was not found !!";
		fout << endl;
	}
	fout.close();						// file close
	free(student_ids); free(students);
	return 0;
}

