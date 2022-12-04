/*Date.cpp*/
#include "Date.h"

istream& operator>>(istream& input, Date& D)
{
	int y, m, d;
	cout << "Input year month day : ";
	input >> y >> m >> d;											// input year month day

	if (D.isValidDate(y, m, d))										// date Valid Check
	{
		D.year = y;
		D.month = m;
		D.day = d;
	}
	else
	{
		cout << "DATE ERROR!! Input Date : " << y << m << d << endl;
		exit(-1);
	}
	return input;
}

ostream& operator<<(ostream& output, const Date& d1)				// operation overloading << 
{
	output << "(" << setw(4) << d1.year << "-" << setw(2) << d1.month << "-" << setw(2) << d1.day << ")";
	return output;													// chained operating
}

int Date::getYearDay() const										// count day form year. 01. 01
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;
	if (isLeapYear(year))											// Leap Year check
		days_month[2] = 29;
	for (int i = 0; i < month; i++)
		yearDay += days_month[i];
	yearDay += day;
	return yearDay;
}

int Date::getWeekDay() const										// check day of the week
{
	int weekDay_AD010101 = 1;										// 010101 is Monday
	int weekDay;
	int elapsedDays = 0;
	elapsedDays = getElapsedDays();									// check the day from 010101
	weekDay = (elapsedDays + weekDay_AD010101 - 1) % 7;
	return weekDay;
}

int Date::getElapsedDays() const									// count day form 01. 01. 01
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < year; y++)
	{
		if (isLeapYear(y))											// LeapYear check
			elpsDay += 366;
		else
			elpsDay += 365;
	}
	yearDay = getYearDay();											// elapsed day form year. 01. 01
	elpsDay += yearDay;
	return elpsDay;
}
bool Date::isValidDate(int y, int m, int d)	const					// Date invalid check
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (y < 1 || m < 1 || m > 12 || d < 1)
	{
		if (isLeapYear(y))											// LeapYear check
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

bool Date::isLeapYear() const										// Check LeapYear
{
	if (Date::isLeapYear(year))										// call isLeapYear(private func)
		return true;
	else
		return false;
}

bool Date::isLeapYear(int y)										// check LeapYear, public func
{
	if (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0)
		return true;
	else
		return false;
}

bool Date::isLeapYear(int y) const									// check LeapYear, public func
{
	if (((y % 4 == 0) && (y % 100 != 0)) || y % 400 == 0)
		return true;
	else
		return false;
}



Date Date::operator=(const Date d1)									// operation overloading =
{
	this->setDate(d1.year, d1.month, d1.day);

	return *this;
}

bool Date::operator>(Date d1) const									// operation overloading >
{
	if (this->getElapsedDays() > d1.getElapsedDays())
		return true;
	else
		return false;
}

bool Date::operator>=(Date d1) const								// operation overloading >
{
	if (this->getElapsedDays() >= d1.getElapsedDays())
		return true;
	else
		return false;
}

bool Date::operator<(Date d1) const									// operation overloading <
{
	if (this->getElapsedDays() < d1.getElapsedDays())
		return true;
	else
		return false;
}

bool Date::operator<=(Date d1) const								// operation overloading <
{
	if (this->getElapsedDays() <= d1.getElapsedDays())
		return true;
	else
		return false;
}

bool Date::operator==(Date d1) const								// operation overloading ==
{
	if (this->getElapsedDays() == d1.getElapsedDays())
		return true;
	else
		return false;
}
bool Date::operator!=(Date d1) const								// operation overloading !=
{
	if (this->getElapsedDays() != d1.getElapsedDays())
		return true;
	else
		return false;
}

/*
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
*/