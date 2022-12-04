/*
* ������Ʈ�� : "��ü�������α׷��� Lab 05-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* - Ŭ����, ������ �����ε�, ����� �̿��Ͽ� �л� �����͸� ó���ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.10.06
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������		����					����			��������
* JH KIM			2022.10.06			v1.0		���� �ۼ�
* JH KIM			2022.10.07			v1.1		StudentArray �Լ� �ۼ�, ���� ����
*/
#include "Class_StudentArray.h"
#include "STD_H.h"
#define NUM_STUDENTS 10
void main()
{
	srand((unsigned int)time(NULL));			// random�� ���� seed ����
	StudentArray studentArray(NUM_STUDENTS);
	Student st;
	ofstream fout;
	int st_ids[NUM_STUDENTS];					// st_id�� ���� array ����
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