#ifndef CLASS_DATE_H
#define CLASS_DATE_H
#include "STD_H.h"

class Date
{
	friend istream& operator>>(istream&, Date&);
	friend ostream& operator<<(ostream&, const Date&);
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor
	void setDate(int newYear, int newMonth, int newDay);
	int getYear() { return year; }
	int getYearDay();
	int getWeekDay();
	int getElapsedDays(); // get elapsed days from AD 1. 1. 1.
	const Date operator=(const Date rightSide);
	bool operator>(Date rightSide);
	bool operator<(Date rightSide);
	bool operator==(Date rightSide);
	bool operator!=(Date rightSide);
	bool isLeapYear(int y); // check whether the given year y is leap year
private:
	bool isLeapYear(); // check whether the year is leap year
	bool isValidDate(int y, int m, int d);
	int year;
	int month;
	int day;
};

bool isLeapYear(int y);
Date genRandDate();

#endif