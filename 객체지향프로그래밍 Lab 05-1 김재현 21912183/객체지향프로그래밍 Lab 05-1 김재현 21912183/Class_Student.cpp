/*Class_Student.cpp*/
#include "Class_Student.h"

Student::Student()						// default constructor
:st_id(0), dept_name("n"), gpa(0.0)
{

}

Student::Student(int id)					// constructor
{
	st_id = id;
	dept_name = ("n");
	gpa = 0.0;
}

Student::Student(int id, string n, Date dob, string dept_n, double gpa)		// default constructor
:Person(n, dob)
{
	st_id = id; dept_name = dept_n;
}


Student genRandStudent(int id)
{
	Student st1(id);

	// Random DeptName
	st1.setDept_name(genRandString(3, 4));

	// Random Date
	st1.setBirthDate(genRandDate());

	// Random Name
	st1.setName(genRandString(4, 7));


	// Random GPA
	double rand_GPA = 0.0;
	rand_GPA = rand() % 10000 / 100.0;
	st1.setGPA(rand_GPA);
	return st1;
}

ostream& operator<<(ostream& fout, const Student& St1)					// chaine operation
{
	fout << "Student[ " << "st_id : " << setw(5) << St1.st_id <<", name : " << setw(7) << St1.name << ", Dept : "
		<< setw(5) << St1.dept_name << ", birth date : " << St1.birthDate;
	fout.setf(ios::showpoint);											// print format setting 
	fout.setf(ios::fixed);					
	fout.precision(2);
	fout << ", GPA : " << setw(6) << St1.gpa << "]" << endl;


	return fout;														// chained operating
}

const Student& Student::operator=(const Student& St1)					// operation overloading =
{                                                                                     
	this->setST_id(St1.st_id);
	this->setName(St1.name);
	this->setDept_name(St1.dept_name);
	this->setBirthDate(St1.birthDate);
	this->setGPA(St1.gpa);
	return *this;
}

bool Student::operator>(const Student& right)							// operation overloading >
{
	if (this->st_id > right.st_id)										// 비교 우선순위 학번->이름->학과->생일->GPA
		return true;
	if (this->name.compare(right.name) > 0)
		return true;
	if (this->dept_name.compare(right.dept_name) > 0)
		return true;
	if (this->birthDate > right.birthDate)
		return true;
	if (this->gpa > right.gpa)
		return true;
	return false;
}

bool Student::operator==(const Student& right) 							// operation overloading ==
{
	if (this->st_id != right.st_id)
		return false;
	if (this->name.compare(right.name) != 0)
		return false;
	if (this->dept_name.compare(right.dept_name) != 0)
		return false;
	if (this->birthDate != right.birthDate)
		return false;
	if (this->gpa != right.gpa)
		return false;
	return true;
}

void genST_ids(int num_students, int* st_ids)							// genRandSt_ids
{
	int count = 0, rand_st_id = 0, r1, r2 =0;			
	int* rand_st_id_array = NULL;
	int offset = 10000;													// offset 10000
	int MAX_SIZE = 30000;

	rand_st_id_array = (int*)calloc(MAX_SIZE, sizeof(int));
	// flag를 사용한 rand array 생성
	/*while (count < 10)
	{
		rand_st_id = rand() % MAX_SIZE;
		if (rand_st_id_array[rand_st_id] == 0)							// rand idx의 값이 0이면 생성되지 않은 숫자로 판단
		{
			rand_st_id_array[rand_st_id] = 1;
			
			st_ids[count] = rand_st_id + offset;
			count++;
		}
	}*/
	// shuffle 을 이용한 rand array 생성
	for (int i = 0; i < MAX_SIZE; i++)
	{
		rand_st_id_array[i] = i;
	}
	for (int i = 0; i < MAX_SIZE; i++)
	{
		r1 = rand() % MAX_SIZE;
		r2 = rand() % MAX_SIZE;
		if (r1 == r2)
			continue;
		rand_st_id = rand_st_id_array[r1];
		rand_st_id_array[r1] = rand_st_id_array[r2];
		rand_st_id_array[r2] = rand_st_id;
	}
	for (int i = 0; i < num_students; i++)
	{
		st_ids[i] = rand_st_id_array[i] + offset;
	}
	free(rand_st_id_array);
}
