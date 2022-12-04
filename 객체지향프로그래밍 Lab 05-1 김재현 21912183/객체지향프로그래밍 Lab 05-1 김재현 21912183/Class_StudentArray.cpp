#include "Class_StudentArray.h"
StudentArray::StudentArray(int size)                    // constructor
{
    num_students = size;
    students = new Student[size];                       // Dynamic Memory Allocation
}

StudentArray::StudentArray(const StudentArray& obj)
{
    students = obj.students;
    num_students = obj.num_students;
}

StudentArray::~StudentArray()                           // destructor
{
    delete[] students;                                  // free memory
}

ostream& operator<<(ostream& fout, const StudentArray& SA1)
{
    fout << "StudentArray (size : " << SA1.num_students << ")" << endl;     // StudentArray size 출력

    for (int i = 0; i < SA1.num_students; i++)                              // printout
        fout << SA1.students[i];

    return fout;                                                            // chained operation
}

void StudentArray::sortByBirthDate()                            // Date를 기준으로 selection sorting
{ 
    int min_idx = 0;
    Student min_value;
    for (int i = 0; i < num_students; i++)
    {
        min_idx = i;
        min_value = students[i];
        for (int p = i; p < num_students; p++)
        {
            if (min_value.getBirthDate() > students[p].getBirthDate())          // overloadin된 연산자 사용
            {
                min_idx = p;
                min_value = students[p];
            }
        }
        if (min_idx != i)                                       // min_idx와 start idx가 다르면 swap
        {
            students[min_idx] = students[i];
            students[i] = min_value;
        }
    }
}

void StudentArray::sortByName()                                 // name를 기준으로 selection sorting
{
    int min_idx = 0;
    Student min_value;
    for (int i = 0; i < num_students; i++)
    {
        min_idx = i;
        min_value = students[i];
        for (int p = i; p < num_students; p++)
        {
            if (min_value.name > students[p].name)
            {
                min_idx = p;
                min_value = students[p];
            }
        }
        if (min_idx != i)                                       // min_idx와 start idx가 다르면 swap
        {
            students[min_idx] = students[i];
            students[i] = min_value;
        }
    }
}

void StudentArray::sortByST_ID()                                // ID를 기준으로 selection sorting
{
    int min_idx = 0;
    Student min_value;
    for (int i = 0; i < num_students; i++)
    {
        min_idx = i;
        min_value = students[i];
        for (int p = i; p < num_students; p++)
        {
            if (min_value.st_id > students[p].st_id)
            {
                min_idx = p;
                min_value = students[p];
            }
        }
        if (min_idx != i)                                       // min_idx와 start idx가 다르면 swap
        {
            students[min_idx] = students[i];
            students[i] = min_value;
        }
    }
}

void StudentArray::sortByGPA()                                // GPA를 기준으로 selection sorting
{
    int min_idx = 0;
    Student min_value;
    for (int i = 0; i < num_students; i++)
    {
        min_idx = i;
        min_value = students[i];
        for (int p = i; p < num_students; p++)
        {
            if (min_value.gpa > students[p].gpa)
            {
                min_idx = p;
                min_value = students[p];
            }
        }
        if (min_idx != i)                                     // min_idx와 start idx가 다르면 swap
        {
            students[min_idx] = students[i];
            students[i] = min_value;
        }
    }
}

bool StudentArray::isValidIndex(int index) const                // index 유효성 검사
{
    if (index < 0 || index> num_students)
        return false;
    else
        return true;
}

Student& StudentArray::operator[] (int sub) const               // operation overloading []
{
    if (isValidIndex(sub))                                     
        return students[sub];
    else
        cout << "Error : Subscript out of range.\n";
    exit(-1);
}