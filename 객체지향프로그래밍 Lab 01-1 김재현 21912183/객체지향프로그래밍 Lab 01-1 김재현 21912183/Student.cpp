/*Student.cpp*/
#include "Student.h"
#include <limits.h>
void initStudents(Student students[], int st_ids[], int num_students)	// initialize Students Structure
{
	int name_len;
	int j, grade;
	double br;
	srand(time(0));
	for (int i = 0; i < num_students; i++)
	{
		students[i].st_id = st_ids[i];
		name_len = rand() % 11 + 5;
		students[i].name[0] = rand() % 26 + 'A';		// �л� �̸��� ù ���ڴ� �빮�ڷ� ����
		for (j = 1; j < name_len; j++)
			students[i].name[j] = rand() % 26 + 'a';	// �л� �̸��� �ι�° ���ں��� �ҹ��ڷ� ����
		students[i].name[j] = '\0';						// �̸��� �������� NULL�Է�
		name_len = (unsigned int)rand() % 4 + 2;						// �а� �̸� ���� ����
		for (j = 0; j < name_len; j++)
			students[i].dept[j] = rand() % 26 + 'A';
		students[i].dept[j] = '\0';						// �а��� �������� NULL �Է�
		students[i].grade = rand() % 8 + 1;
		students[i].gpa = (rand() % 10000) / 100.0;		// GPA:0~99.99
	}
}

void fprintStudents(ostream& fout, Student* students, int num_students)		// �л� �Ѹ��� Data�� ����ϴ� �Լ�
{
	fout.setf(ios::fixed);			// ���� �Ҽ���
	fout.setf(ios::showpoint);		// �Ҽ��� ���ϸ� ���
	fout.precision(2);				// �Ҽ��� ��� ���е� ����
	for (int i = 0; i < num_students; i++)
	{
		fout << "Student(ID: " << setw(4) << students[i].st_id;
		fout << ", Name: " << setw(16) << students[i].name;		// ��� 16ĭ Ȯ���� name ���
		fout << ", Dept : " << setw(6) << students[i].dept;		// ��� 6ĭ Ȯ���� dept ���
		fout << ", Grade : " << students[i].gpa << endl;		// ��� �Ϸ� �� �ٹٲ�
	}
}

void fprintStudent(ostream& fout, Student* pSt)
{
	fout.setf(ios::fixed);		// ���� �Ҽ���
	fout.setf(ios::showpoint);	// �Ҽ��� ���ϸ� ���
	fout.precision(2);			// �Ҽ��� ��� ���е� ����
	fout << "Student(ID: " << setw(4) << pSt->st_id;
	fout << ", Name: " << setw(16) << pSt->name;				// ��� 16ĭ Ȯ���� name ���
	fout << ", Dept : " << setw(6) << pSt->dept;				// ��� 6ĭ Ȯ���� dept ���
	fout << ", Grade : " << pSt->gpa;
}

void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last)
{
	Student* pSt;
	int count = 0;
	if (num_students <= num_first_last * 2)
	{
		for (int i = 0; i < num_students; i++)
		{
			pSt = &students[i];
			fout << setw(6) << pSt->st_id;			// 6ĭ�� st_id ���
			count++;
			if ((count % 20) == 0)					// 1�ٿ� 20�� ����� �ٹٲ�
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++)
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;				// 6ĭ�� st_id ���
		count++;
		if ((count % 20) == 0)						// 1�ٿ� 20�� ����� �ٹٲ�
			fout << endl;
	}
	fout << " . . . . . " << endl;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;				// 6ĭ�� st_id ���
		count++;
		if ((count % 20) == 0)						// 1�ٿ� 20�� ����� �ٹٲ�
			fout << endl;
	}
}

void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last)		// GPA�� ID�� ����ϴ� �Լ�
{
	Student* pSt;
	int count = 0;
	fout.setf(ios::fixed);		// ���� �Ҽ���
	if (num_students <= num_first_last * 2)		// �� �� ������ ũ�⺸�� ��ü ũ�Ⱑ �������
	{
		for (int i = 0; i < num_students; i++)
		{
			pSt = &students[i];
			fout << "(" << setprecision(2) << pSt->gpa << "," << setw(5) << pSt->st_id << ") ";		// gpa, st_id ���
			count++;
			if ((count % 20) == 0)
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++)
	{
		pSt = &students[i];
		fout << "(" << setprecision(2) << pSt->gpa << "," << setw(5) << pSt->st_id << ") ";			// gpa, st_id ���
		count++;
		if ((count % 20) == 0)
			fout << endl;
	}
	fout << " . . . . . " << endl;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = &students[i];
		fout << "(" << setprecision(2) << pSt->gpa << "," << setw(5) << pSt->st_id << ") ";			// gpa, st_id ���
		count++;
		if ((count % 20) == 0)
			fout << endl;
	}
}

void selectionSortStudentsBy_ID(Student students[], int num_students)		// id�� �������� selectionsorting�ϴ� �Լ�
{
	int min_id = INT_MAX, min_idx = 0;	// min_id�� int���� �ִ�� ����
	Student temp;
	for (int i= 0; i < num_students-1; i++)				// ������ �񱳴� i+1�� ������ ���� �� �̷����
	{
		min_id = students[i].st_id;
		min_idx = i;
		for (int p = i; p < num_students; p++)
		{
			if (min_id > students[p].st_id)				// �� ���� id���� ã�� ���
			{
				min_id = students[p].st_id;
				min_idx = p;
			}
		}
		if (min_idx != i)	// swap
		{
			temp = students[i];
			students[i] = students[min_idx];
			students[min_idx] = temp;
		}
	}
}

void selectionSortStudentsBy_GPA(Student students[], int num_students)			// GPA score �������� selection sorting
{
	double max_GPA;
	int max_idx = 0;
	Student temp;
	for (int i = 0; i < num_students - 1; i++)			// ������ �񱳴� i+1�� ������ ���� �� �̷����
	{
		max_GPA = students[i].gpa;
		max_idx = i;
		for (int p = i; p < num_students; p++)
		{
			if (max_GPA < students[p].gpa)				// �� ū gpa���� ã�� ���
			{
				max_GPA = students[p].gpa;
				max_idx = p;
			}
		}
		if (max_idx != i)	// swap
		{
			temp = students[i];
			students[i] = students[max_idx];
			students[max_idx] = temp;
		}
	}
	for (int i = 0; i < num_students - 1; i++)
	{
		if ((students[i].gpa == students[i + 1].gpa) && (students[i].st_id > students[i + 1].st_id))		// GPA score�� ���� �� id ������������ ����
		{
			temp = students[i];
			students[i] = students[i + 1];
			students[i + 1] = temp;
		}
	}
}

Student* binarySearchStudentByID(Student* students, int num_students, int st_id)			// id�� �������� binary search
{
	int low, high, mid;
	low = 0;
	high = num_students - 1;		// array�� idx 0���� �����ϹǷ� ���� num - 1
	while (low <= high)				// low�� high���� �۰ų� ������ �ݺ�
	{
		mid = (low + high) / 2;
		if (st_id == students[mid].st_id)			// value search�� ������ ��� �ش� �л� data�� address return
			return &students[mid];
		else if (st_id < students[mid].st_id)
			high = mid - 1;
		else
			low = mid + 1;
	}
}