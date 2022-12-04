/*Date.cpp*/
#include "Date.h"
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTH { JAN = 1, FED, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, NUM_MONTHS };

const char* weekDayName[DAYS_PER_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const char* weekDayNameShort[DAYS_PER_WEEK] = { "SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT" };
const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

//default constructor
Date::Date()
{
	year = 0;
	month = 0;
	day = 0;
}
Date::Date(int y, int m, int d)	// constructor
:year(y), month(m), day(d)		// initialize year, month, day
{
	
}

//default destructor
Date::~Date()
{
	// cout << "Date object instance is destructed" << endl;
}

bool Date::isValidDate(int y, int m, int d)		// �������� ������ Ȯ��
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (isLeapYear(y))
		days_month[2] = 29;
	if ((m >= 1) && (m <= 12) && (d >= 1) && (d <= days_month[m]))		// ���� ���̸� true ��ȯ
	{
		return true;
	}
	else {
		cout << "Illegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}

void Date::setDate(int y, int m, int d)
{
	if (isValidDate(y, m, d))		// �������� �� ���� Ȯ�� �� �����̸� setDate
	{
		year = y;
		month = m;
		day = d;
	}
	else {
		cout << "Invalid date (" << y << ", " << m << ", " << d << ")";
		cout << " Program aborted !!\n";
		exit(1);
	}
}

void Date::setRandDateAttributes()		// Random Date Generator
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	year = rand() % 2000 + 1000;	// 1000~3000
	month = rand() % 12 + 1;		// 1~12
	if (isLeapYear(year) && month == 2)
		days_month[2] = 29;
	day = rand() % days_month[month] + 1;
}

void Date::setMonth(int newMonth)
{
	if ((newMonth >= 1) && (newMonth <= 12))		// �������� ���� �ƴϸ� �Է����� ����
		month = newMonth;
	else
	{
		cout << "Illegal month value! Program aborted.\n";
		exit(1);
	}
	day = 1;
}

void Date::setYear(int y)
{
	year = y;
}

int Date::getYearDay()
{
	int yearDay;
	yearDay = getYearDay(month, day);
	return yearDay;
}

int Date::getYearDay(int month, int day)			// 1�� 1�Ϻ��� �ش� ��¥���� ���ذ� �󸶳� �������� Ȯ��
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;
	if (isLeapYear(year))		// �����̸� 2���� 29�ϱ���
		days_month[2] = 29;
	for (int i = 0; i < month; i++)
		yearDay += days_month[i];
	yearDay += day;
	
	return yearDay;
}

int Date::getElapsedDaysFromAD010101()				// call getElapsedDaysFromAD010101
{
	int elpsDay = 0;
	elpsDay = getElapsedDaysFromAD010101(*this);
	return elpsDay;
}

int Date::getElapsedDaysFromAD010101(Date d)		// ���� 1�� 1�� 1�Ϸ� ���� ��ĥ°���� �����ϴ� �Լ�
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < d.year; y++)
	{
		if (isLeapYear(y))							// �����̸� +366
			elpsDay += 366;
		else
			elpsDay += 365;
	}
	yearDay = getYearDay(d.month, d.day);			// ���ذ� �󸶳� �������� check
	elpsDay += yearDay;
	return elpsDay;
}
int Date::getWeekDay()
{
	int weekDay_AD010101 = MON; // 1. 1. 1. is Monday
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDaysFromAD010101();
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7;
	//cout << ", Elapsed days from AD Jan. 1, 1 (" << elapsedDays << ")";
	return weekDay;
}

void Date::inputDate()		// Date�� �Է¹޾� �����ϴ� �Լ�
{
	int y, m, d;
	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;
	if (isValidDate(y, m, d))		// �������� value���� check
	{
		year = y;
		month = m;
		day = d;
	}
	else {
		cout << "Ilegal date! Program aborted.\n";
		exit(1);
	}
}

bool Date::isLeapYear()		// call isLeapYear
{
	if (isLeapYear(year))
		return true;
	else
		return false;
}

bool Date::isLeapYear(int y)		// check LeapYear
{
	if (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0)
		return true;
	else
		return false;
}


void Date::fprintDate(ostream& fout)		// printout Date
{
	// weekdayname, monthname�� �ֻ�ܿ� ������ ���� ���
	//const char* weekDayName[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	//const char* monthName[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	int yearDay = 0;
	int weekDay;
	if ((month >= 1) && (month <= 12))			// printout
		fout << setw(10) << string(monthName[month]);
	fout << " " << setw(2) << day << ", " << setw(4) << year;
	yearDay = getYearDay();
	weekDay = getWeekDay();
	fout << " (" << setw(10) << string(weekDayName[weekDay]) << ")";
}