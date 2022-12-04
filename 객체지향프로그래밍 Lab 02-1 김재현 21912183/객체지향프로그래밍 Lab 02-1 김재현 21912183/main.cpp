/*
* 프로젝트명 : "객체지향프로그래밍 Lab 02-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - 클래스 Date, Person을 이용하여 날짜연산 및 Person Data를 관리하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.09.15
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자		일자			버전		수정내용
* JH KIM			2022.09.15			v1.0		최초 작성
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
	srand(time(NULL));								// time 기반으로 random
	/*Part 01. Date data Handling*/
	ofstream fout;									// output file stream
	fout.open("output.txt");						// file open
	if (fout.fail())								// file state check
	{
		cout << "Error in opening output.txt !!" << endl;
		exit;
	}
	Date AD010101(1, 1, 1);							// AD010101을 1년 1월 1일로 init
	int year, month, day;
	int daysToChristmas;
	time_t currentTime;
	struct tm* time_and_date;
	time(&currentTime);								// 현재 시간 측정
	time_and_date = localtime(&currentTime);		// localtime으로 수정하여 저장

	year = time_and_date->tm_year + 1900;			// 년, 월, 일을 오늘 날짜에 맞게 수정
	month = time_and_date->tm_mon + 1;
	day = time_and_date->tm_mday;

	Date newYearDay(year, 1, 1), today(year, month, day), christmas(2022, 12, 25);		// newYearDay, today, christmas init
	fout << "AD Jan. 1, 1 is ";
	AD010101.fprintDate(fout);						// 01년 01월 01일 파일 출력
	fout << endl;

	fout << "Today is ";
	today.fprintDate(fout);							// 현재 날짜 파일 출력
	fout << endl;

	fout << "New year's day of this year was ";		// 올해 신정에 대한 데이터 출력
	newYearDay.fprintDate(fout);
	fout << endl;

	
	fout << "Christmas of this year is ";			// 크리스마스에 대한 데이터 출력
	christmas.fprintDate(fout);
	fout << endl;

	if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())		// 오늘 날짜와 크리스마스 날짜 비교
	{
		fout << "Today is Christmas! Happy Christmas to you all !!\n";
	}
	else
	{
		fout << " Sorry, today is not Christmas!\n";
		daysToChristmas = christmas.getElapsedDaysFromAD010101() - today.getElapsedDaysFromAD010101();		// 오늘부터 크리스마스까지 남은 날짜
		fout << " You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
	}
	fout << endl;

	/*Date data handling finished point*/
	/*===============================================================================================*/
	/*Part 02. Person data handling*/

	Person p1(string("Hong, Gil-Dong"), Date(2000, 1, 1)), p2;		// p1, p2 객체 생성
	fout << "Person p1 : " << endl;					// p1 출력
	p1.fprintPerson(fout);
	fout << endl;

	fout << "Person p2 : " << endl;					// p2 출력
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
