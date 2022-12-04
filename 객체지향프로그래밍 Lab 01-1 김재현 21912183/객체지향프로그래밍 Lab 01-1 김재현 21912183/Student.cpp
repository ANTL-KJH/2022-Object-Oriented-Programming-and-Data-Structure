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
		students[i].name[0] = rand() % 26 + 'A';		// 학생 이름의 첫 글자는 대문자로 설정
		for (j = 1; j < name_len; j++)
			students[i].name[j] = rand() % 26 + 'a';	// 학생 이름의 두번째 글자부터 소문자로 설정
		students[i].name[j] = '\0';						// 이름의 마지막에 NULL입력
		name_len = (unsigned int)rand() % 4 + 2;						// 학과 이름 길이 설정
		for (j = 0; j < name_len; j++)
			students[i].dept[j] = rand() % 26 + 'A';
		students[i].dept[j] = '\0';						// 학과명 마지막에 NULL 입력
		students[i].grade = rand() % 8 + 1;
		students[i].gpa = (rand() % 10000) / 100.0;		// GPA:0~99.99
	}
}

void fprintStudents(ostream& fout, Student* students, int num_students)		// 학생 한명의 Data를 출력하는 함수
{
	fout.setf(ios::fixed);			// 고정 소수점
	fout.setf(ios::showpoint);		// 소수점 이하를 출력
	fout.precision(2);				// 소수점 출력 정밀도 설정
	for (int i = 0; i < num_students; i++)
	{
		fout << "Student(ID: " << setw(4) << students[i].st_id;
		fout << ", Name: " << setw(16) << students[i].name;		// 출력 16칸 확보후 name 출력
		fout << ", Dept : " << setw(6) << students[i].dept;		// 출력 6칸 확보후 dept 출력
		fout << ", Grade : " << students[i].gpa << endl;		// 출력 완료 후 줄바꿈
	}
}

void fprintStudent(ostream& fout, Student* pSt)
{
	fout.setf(ios::fixed);		// 고정 소수점
	fout.setf(ios::showpoint);	// 소수점 이하를 출력
	fout.precision(2);			// 소수점 출력 정밀도 설정
	fout << "Student(ID: " << setw(4) << pSt->st_id;
	fout << ", Name: " << setw(16) << pSt->name;				// 출력 16칸 확보후 name 출력
	fout << ", Dept : " << setw(6) << pSt->dept;				// 출력 6칸 확보후 dept 출력
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
			fout << setw(6) << pSt->st_id;			// 6칸에 st_id 출력
			count++;
			if ((count % 20) == 0)					// 1줄에 20개 출력후 줄바꿈
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++)
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;				// 6칸에 st_id 출력
		count++;
		if ((count % 20) == 0)						// 1줄에 20개 출력후 줄바꿈
			fout << endl;
	}
	fout << " . . . . . " << endl;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;				// 6칸에 st_id 출력
		count++;
		if ((count % 20) == 0)						// 1줄에 20개 출력후 줄바꿈
			fout << endl;
	}
}

void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last)		// GPA와 ID를 출력하는 함수
{
	Student* pSt;
	int count = 0;
	fout.setf(ios::fixed);		// 고정 소수점
	if (num_students <= num_first_last * 2)		// 앞 뒤 샘플의 크기보다 전체 크기가 작은경우
	{
		for (int i = 0; i < num_students; i++)
		{
			pSt = &students[i];
			fout << "(" << setprecision(2) << pSt->gpa << "," << setw(5) << pSt->st_id << ") ";		// gpa, st_id 출력
			count++;
			if ((count % 20) == 0)
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++)
	{
		pSt = &students[i];
		fout << "(" << setprecision(2) << pSt->gpa << "," << setw(5) << pSt->st_id << ") ";			// gpa, st_id 출력
		count++;
		if ((count % 20) == 0)
			fout << endl;
	}
	fout << " . . . . . " << endl;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = &students[i];
		fout << "(" << setprecision(2) << pSt->gpa << "," << setw(5) << pSt->st_id << ") ";			// gpa, st_id 출력
		count++;
		if ((count % 20) == 0)
			fout << endl;
	}
}

void selectionSortStudentsBy_ID(Student students[], int num_students)		// id를 기준으로 selectionsorting하는 함수
{
	int min_id = INT_MAX, min_idx = 0;	// min_id는 int값의 최대로 설정
	Student temp;
	for (int i= 0; i < num_students-1; i++)				// 마지막 비교는 i+1이 마지막 값일 때 이루어짐
	{
		min_id = students[i].st_id;
		min_idx = i;
		for (int p = i; p < num_students; p++)
		{
			if (min_id > students[p].st_id)				// 더 작은 id값을 찾은 경우
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

void selectionSortStudentsBy_GPA(Student students[], int num_students)			// GPA score 기준으로 selection sorting
{
	double max_GPA;
	int max_idx = 0;
	Student temp;
	for (int i = 0; i < num_students - 1; i++)			// 마지막 비교는 i+1이 마지막 값일 때 이루어짐
	{
		max_GPA = students[i].gpa;
		max_idx = i;
		for (int p = i; p < num_students; p++)
		{
			if (max_GPA < students[p].gpa)				// 더 큰 gpa값을 찾은 경우
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
		if ((students[i].gpa == students[i + 1].gpa) && (students[i].st_id > students[i + 1].st_id))		// GPA score가 같을 때 id 오름차순으로 정렬
		{
			temp = students[i];
			students[i] = students[i + 1];
			students[i + 1] = temp;
		}
	}
}

Student* binarySearchStudentByID(Student* students, int num_students, int st_id)			// id를 기준으로 binary search
{
	int low, high, mid;
	low = 0;
	high = num_students - 1;		// array는 idx 0부터 시작하므로 끝은 num - 1
	while (low <= high)				// low가 high보다 작거나 같으면 반복
	{
		mid = (low + high) / 2;
		if (st_id == students[mid].st_id)			// value search에 성공한 경우 해당 학생 data의 address return
			return &students[mid];
		else if (st_id < students[mid].st_id)
			high = mid - 1;
		else
			low = mid + 1;
	}
}