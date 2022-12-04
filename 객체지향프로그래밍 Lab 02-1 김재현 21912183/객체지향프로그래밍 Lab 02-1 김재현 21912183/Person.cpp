#include "Person.h"

void Person::setRandPersonAttributes()
{
	char str[MAX_NAME_LEN + 1];
	int name_len, i = 0;
	birthDate.setRandDateAttributes();										// Random Birthday generator
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;		// Random name generator
	str[0] = rand() % 26 + 'A';				// �̸��� ù���ڴ� �빮��
	for (i = 1; i < name_len; i++)
		str[i] = rand() % 26 + 'a';
	str[i] = '\0';							// �̸��� ������ NULL ǥ��
	name = string(str);
}

void Person::fprintPerson(ostream& fout)
{
	fout << " Person [name: ";
	fout.setf(ios::left);		// ���� ����
	fout << setw(16) << name;	// 16ĭ �Ҵ� �� ���
	fout << ", birth date: ";
	fout.unsetf(ios::left);		// ���� ����
	birthDate.fprintDate(fout);	// Date ���
	fout << "]";
}