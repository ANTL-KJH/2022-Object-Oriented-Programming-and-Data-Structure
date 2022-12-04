/*
* 프로젝트명 : "객체지향프로그래밍 Lab 05-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - 클래스, 연산자 오버로딩, 상속을 이용하여 학생 데이터를 처리하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.10.06
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자		일자					버전			수정내용
* JH KIM			2022.10.06			v1.0		최초 작성
* JH KIM			2022.10.07			v1.1		StudentArray 함수 작성, 오류 수정
*/
#include "Class_StudentArray.h"
#include "STD_H.h"
#define NUM_STUDENTS 10
void main()
{
	srand((unsigned int)time(NULL));			// random을 위한 seed 설정
	StudentArray studentArray(NUM_STUDENTS);
	Student st;
	ofstream fout;
	int st_ids[NUM_STUDENTS];					// st_id를 담을 array 선언
	fout.open("output.txt");					// file open
	if (fout.fail())							// file check
	{
		cout << "Fail to open an output file (output.txt)\n";
		exit(1);
	}

	genST_ids(NUM_STUDENTS, st_ids);			// random student id
	fout << "Initializing student array (num_students: " << NUM_STUDENTS << ")" << endl;

	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		st = genRandStudent(st_ids[i]);			// gen random student
		studentArray[i] = st;
	}
	fout << studentArray;
	fout << "\nSorting studentArray by student id : " << endl;		// sorting by id
	studentArray.sortByST_ID();
	fout << studentArray;
	fout << "\nSorting studentArray by student name : " << endl;	// sorting by name
	studentArray.sortByName();
	fout << studentArray;
	fout << "\nSorting studentArray by GPA : " << endl;				// sorting by gpa
	studentArray.sortByGPA();
	fout << studentArray;
	fout << "\nSorting studentArray by BirthDate : " << endl;		// sorting by bd
	studentArray.sortByBirthDate();
	fout << studentArray;
	fout << endl;
	fout.close();
}