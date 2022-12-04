/*
* 프로젝트명 : "객체지향프로그래밍 Lab 07-2 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - STL vector를 이용하여 학생 데이터를 처리하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.10.20
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자		일자					버전			수정내용
* JH KIM				2022.10.20				v1.0		최초 작성
*/
#include <iostream>
#include "Class_T_Array.h"
#include "Student.h"
using namespace std;
#define NUM_STUDENTS 10

int main()
{
	Student students[NUM_STUDENTS] =					// student array
	{
		Student(5555, "Kim", 10205, "Korea", 3.57),
		Student(1234, "Lee", 11213, "Korea", 4.37),
		Student(4444, "Park", 12227, "Korea", 3.72),
		Student(2222, "Hao", 10121, "China", 2.35),
		Student(3333, "James", 11219, "USA", 3.89),
		Student(6666, "Thomas", 12320, "UK", 4.42),
		Student(7777, "Leon", 10722, "France", 4.12),
		Student(9999, "Carlo", 11519, "Italy", 4.35),
		Student(1000, "Tanaka", 13920, "Japan", 3.21),
		Student(8888, "Wang", 10622, "China", 3.45),
	};
	Student* pSt;

	T_Array<Student*, int> stArray_keySTID(NUM_STUDENTS, "T_Array<Student, keyST_ID>");							// Template array, T=Student*, K=int
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keySTID.insert(i, &students[i]);
	}
	cout << "T_Array<Student*_keyID> at initialization :" << endl;
	stArray_keySTID.print(1);																					// printout

	stArray_keySTID.selection_sort(string("ST_ID"), INCREASING);												// selection sorting, Sortingorder = INCREASING
	cout << "\nT_Array<Student*, keyID> after selection sorting (increasing order) by ST_ID : " << endl;
	stArray_keySTID.print(1);

	T_Array<Student*, string> stArray_keyName(NUM_STUDENTS, "T_Array<Student, keyName>");						// Template array, T=Student*, K=string
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyName.insert(i, &students[i]);
	}
	stArray_keyName.selection_sort(string("NAME"), INCREASING);													// selection sorting, Sortingorder = INCREASING
	cout << "T_Array<Student*_keyName> after selection_sorting (increasing order) by Name : " << endl;
	stArray_keyName.print(1);																					// printout

	T_Array<Student*, double> stArray_keyGPA(NUM_STUDENTS, "T_Array<Student, keyGPA>");							// Template array, T=Student*, K=double
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyGPA.insert(i, &students[i]);
	}
	stArray_keyGPA.selection_sort(string("GPA"), DECREASING);													// selection sorting, Sortingorder = DECREASING
	cout << "T_Array<Student*_keyGPA> after selection_sorting (decreasing order) by GPA : " << endl;
	stArray_keyGPA.print(1);																					// printout

	T_Array<Student*, int> stArray_keyRegID(NUM_STUDENTS, "T_Array<Student, keyRegID>");						// Template array, T=Student*, K=int
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyRegID.insert(i, &students[i]);
	}
	stArray_keyRegID.merge_sort(string("REGID"), INCREASING);													// merge sorting, Sortingorder = INCREASING
	cout << "\nT_Array<Student*_keyRegID> after merge sorting (increasing order) by regID : " << endl;
	stArray_keyRegID.print(1);																					// printout

	T_Array<Student*, string> stArray_keyNation(NUM_STUDENTS, "T_Array<Student, keyNation>");					// Template array, T=Student*, K=string
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyNation.insert(i, &students[i]);
	}
	stArray_keyNation.merge_sort(string("NATION"), INCREASING);													// merge sorting, Sortingorder = INCREASING
	cout << "\nT_Array<Student*_keyNation> after merge sorting (increasing order) by nation : " << endl;
	stArray_keyNation.print(1);																					// printout

	return 0;
}