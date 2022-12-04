/*
* 프로젝트명 : "객체지향프로그래밍 Lab 07-1 김재현 21912183"
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
#include "Student.h"
#include "VectorHandler.h"
using namespace std;
#define NUM_STUDENTS 10

int main(void)
{
	Student students[NUM_STUDENTS] =				// Student Array Data
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
	
	vector<Student> v_students(students, students + NUM_STUDENTS);			// STL vector array 생성 "Kim" ~ "Wang"
	cout << "Initial v_students :" << endl;
	printVector(v_students);												// print out
	sort(v_students.begin(), v_students.end());								// sorting
	cout << "\nstudents after sorting by st_id :" << endl;
	printVector(v_students);												// printout
	return 0;
}