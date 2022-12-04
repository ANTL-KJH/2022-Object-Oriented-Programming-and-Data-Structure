/*
* 프로젝트명 : "객체지향프로그래밍 Lab 01-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* -32,767보다 큰 난수의 배열을 생성하고 학생 구조체를 출력하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.08.31
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자		일자			버전		수정내용
* JH KIM			2022.08.31	v1.0	최초 작성
* JH KIM			2022.09.01	v1.1	함수 작성
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
	if (fout.fail())				// file open에 실패한경우 exit
	{
		cout << "Error in opening output.txt" << endl;
		exit;
	}
	students = (Student*)calloc(NUM_STUDENTS, sizeof(Student));		// Dynamic Memory Allocation
	student_ids = genBigRandArray(NUM_STUDENTS, 0);					// Bigrandom을 생성하여 student_ids에 입력
	initStudents(students, student_ids, NUM_STUDENTS);				// initialize Student Structure array

	fout << endl << endl;
	fout << "Initialized array of students : " << endl;
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);	// BigRand로 생성한 학생의 id를 앞뒤 100개씩 샘플을 추출하여 출력
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);									// id를 기준으로 selection sorting
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Sorting array of students by (decreasing order of GPA, increasing order of ID) : " << endl;
	selectionSortStudentsBy_GPA(students, NUM_STUDENTS);								// GPA 내림차순 정렬, GPA가 같을 때 id 오름차순 정렬
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);									// id를 기준으로 selection sorting
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	fout << endl << endl;
	fout << "Searching student with student_ID : " << endl;
	for (int i = 0; i < NUM_SEARCH; i++)
	{
		pSt = binarySearchStudentByID(students, NUM_STUDENTS, student_search[i]);		// ID를 기준으로 이진탐색
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

