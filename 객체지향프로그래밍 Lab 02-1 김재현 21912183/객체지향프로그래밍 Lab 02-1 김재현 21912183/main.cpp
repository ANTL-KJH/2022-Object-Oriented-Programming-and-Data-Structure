/*
* ������Ʈ�� : "��ü�������α׷��� Lab 02-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* - Ŭ���� Date, Person�� �̿��Ͽ� ��¥���� �� Person Data�� �����ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.09.15
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������		����			����		��������
* JH KIM			2022.09.15			v1.0		���� �ۼ�
*/
#include <iostream>
#include <fstream>
#include <time.h> // for time(), localtime(), time_t, struct tm
#include <string>
#include "Date.h"
#include "Person.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define NUM_PERSON 10
int main()
{
	srand(time(NULL));								// time ������� random
	/*Part 01. Date data Handling*/
	ofstream fout;									// output file stream
	fout.open("output.txt");						// file open
	if (fout.fail())								// file state check
	{
		cout << "Error in opening output.txt !!" << endl;
		exit;
	}
	Date AD010101(1, 1, 1);							// AD010101�� 1�� 1�� 1�Ϸ� init
	int year, month, day;
	int daysToChristmas;
	time_t currentTime;
	struct tm* time_and_date;
	time(&currentTime);								// ���� �ð� ����
	time_and_date = localtime(&currentTime);		// localtime���� �����Ͽ� ����

	year = time_and_date->tm_year + 1900;			// ��, ��, ���� ���� ��¥�� �°� ����
	month = time_and_date->tm_mon + 1;
	day = time_and_date->tm_mday;

	Date newYearDay(year, 1, 1), today(year, month, day), christmas(2022, 12, 25);		// newYearDay, today, christmas init
	fout << "AD Jan. 1, 1 is ";
	AD010101.fprintDate(fout);						// 01�� 01�� 01�� ���� ���
	fout << endl;

	fout << "Today is ";
	today.fprintDate(fout);							// ���� ��¥ ���� ���
	fout << endl;

	fout << "New year's day of this year was ";		// ���� ������ ���� ������ ���
	newYearDay.fprintDate(fout);
	fout << endl;

	
	fout << "Christmas of this year is ";			// ũ���������� ���� ������ ���
	christmas.fprintDate(fout);
	fout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())		// ���� ��¥�� ũ�������� ��¥ ��
	{
		fout << "Today is Christmas! Happy Christmas to you all !!\n";
	}
	else
	{
		fout << " Sorry, today is not Christmas!\n";
		daysToChristmas = christmas.getElapsedDaysFromAD010101() - today.getElapsedDaysFromAD010101();		// ���ú��� ũ������������ ���� ��¥
		fout << " You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
	}
	fout << endl;

	/*Date data handling finished point*/
	/*===============================================================================================*/
	/*Part 02. Person data handling*/

	Person p1(string("Hong, Gil-Dong"), Date(2000, 1, 1)), p2;		// p1, p2 ��ü ����
	fout << "Person p1 : " << endl;					// p1 ���
	p1.fprintPerson(fout);
	fout << endl;

	fout << "Person p2 : " << endl;					// p2 ���
	p2.setName(string("Lee, Soo - Jeong"));			// p2 setname
	p2.setBirthDate(Date(2018, 9, 1));
	p2.fprintPerson(fout);

	fout << endl;
	fout << endl << "Generating array of persons ... " << endl;

	Person* persons;								
	persons = (Person*) new Person[NUM_PERSON];		// Dynamic Memory Allocation
	for (int i = 0; i < NUM_PERSON; i++)
	{
		persons[i].setRandPersonAttributes();
		persons[i].fprintPerson(fout);
		fout << endl;
	}
	fout << endl;
	delete[] persons;
	fout.close();
	return 0;
}
