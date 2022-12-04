/*Class_Date.cpp*/
#include "Class_Date.h"

Date::Date()						// default constructor
:year(0), month(0),day(0)
{

}
Date::Date(int y, int m, int d)					// constructor
{
	year = y; month = m; day = d;
}

void Date::setDate(int newYear, int newMonth, int newDay)			// setDate
{
	year = newYear; month = newMonth; day = newDay;
}

istream& operator>>(istream& input, Date& D)
{
	int y, m, d;
	cout << "Input year month day : ";
	input >> y >> m >> d;							// year month day input

	if (D.isValidDate(y, m, d))						// date check
	{
		D.year = y;
		D.month = m;
		D.day = d;
	}
	else
	{												// invalidDate
		cout << "DATE ERROR!! Input Date : " << y << m << d << endl;
		exit(-1);
	}

	return input;
}

ostream& operator<<(ostream& output, const Date& d1)		// operation overloading << 
{
	output << "(" << setw(4) << d1.year << "-" << setw(2) << d1.month << "-" << setw(2) << d1.day << ")";
	return output;											// chained operating
}

int Date::getYearDay()										// 1월 1일로부터 얼마가 지났는지 구하는 함수
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;
	if (isLeapYear(year))		// 윤년이면 2월은 29일까지
		days_month[2] = 29;
	for (int i = 0; i < month; i++)
		yearDay += days_month[i];
	yearDay += day;

	return yearDay;
}

int Date::getWeekDay()										// getWeekDay 요일 확인
{
	int weekDay_AD010101 = 1; // 1. 1. 1. is Monday
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDays();							// 1년 1월 1일로부터 얼마나 지났는지 확인
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7;
	return weekDay;
}

int Date::getElapsedDays()									// 1년 1월 1일부터 날짜 counting
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < year; y++)
	{
		if (isLeapYear(y))							// 윤년이면 +366
			elpsDay += 366;
		else
			elpsDay += 365;
	}
	yearDay = getYearDay();			// 올해가 얼마나 지났는지 check
	elpsDay += yearDay;
	return elpsDay;
}
bool Date::isValidDate(int y, int m, int d)					// 날짜 유효성 검증
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (y < 1 || m < 1 || m > 12 || d < 1)
	{
		if (isLeapYear(y))									// 윤년 check
		{
			days_month[2] = 29;
		}		
		if (d > days_month[m])
		{
			cout << "ERROR :: ValidDate !!";
			return false;
		}
	}
	return true;
}

bool Date::isLeapYear()				// call isLeapYear, private func
{
	if (isLeapYear(year))
		return true;
	else
		return false;
}

bool Date::isLeapYear(int y)		// check LeapYear, public func
{
	if (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0)
		return true;
	else
		return false;
}

bool isLeapYear(int y)				// check LeapYear, public func
{
	if (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0)
		return true;
	else
		return false;
}

Date genRandDate()					// genRandDate year(2000~3000), month(1~12), day(1~31)
{
	Date rand_date;
	int rand_y = 0;
	int rand_m = 0;
	int rand_d = 0;
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	rand_y = rand() % 1000 + 2000;
	rand_m = rand() % 12 + 1;
	if (isLeapYear(rand_y))
	{
		days_month[2] = 29;
	}
	rand_d = rand() % days_month[rand_m] + 1;
	rand_date.setDate(rand_y, rand_m, rand_d);
	return rand_date;
}

const Date Date::operator=(const Date d1)			// operation overloading =
{
	this->setDate(d1.year, d1.month, d1.day);

	return *this;
}

bool Date::operator>(Date d1)						// operation overloading >
{
	if (this->getElapsedDays() > d1.getElapsedDays())
		return true;
	else
		return false;
}

bool Date::operator<(Date d1)						// operation overloading <
{
	if (this->getElapsedDays() < d1.getElapsedDays())
		return true;
	else
		return false;
}
bool Date::operator==(Date d1)						// operation overloading ==
{
	if (this->getElapsedDays() == d1.getElapsedDays())
		return true;
	else
		return false;
}
bool Date::operator!=(Date d1)						// operation overloading !=
{
	if (this->getElapsedDays() != d1.getElapsedDays())
		return true;
	else
		return false;
}