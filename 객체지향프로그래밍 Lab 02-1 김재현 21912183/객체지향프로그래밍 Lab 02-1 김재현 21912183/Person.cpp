#include "Person.h"

void Person::setRandPersonAttributes()
{
	char str[MAX_NAME_LEN + 1];
	int name_len, i = 0;
	birthDate.setRandDateAttributes();										// Random Birthday generator
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;		// Random name generator
	str[0] = rand() % 26 + 'A';				// 이름의 첫문자는 대문자
	for (i = 1; i < name_len; i++)
		str[i] = rand() % 26 + 'a';
	str[i] = '\0';							// 이름의 끝에는 NULL 표기
	name = string(str);
}

void Person::fprintPerson(ostream& fout)
{
	fout << " Person [name: ";
	fout.setf(ios::left);		// 왼쪽 정렬
	fout << setw(16) << name;	// 16칸 할당 후 출력
	fout << ", birth date: ";
	fout.unsetf(ios::left);		// 정렬 해제
	birthDate.fprintDate(fout);	// Date 출력
	fout << "]";
}