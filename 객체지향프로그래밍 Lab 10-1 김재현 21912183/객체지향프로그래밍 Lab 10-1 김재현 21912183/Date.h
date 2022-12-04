/*Date.h*/
#ifndef DATE
#define DATE
#include <iostream>
#include <iomanip>
using namespace std;

class Date
{
	friend istream& operator>>(istream&, Date&);
	friend ostream& operator<<(ostream&, const Date&);
public:
	Date() :year(-1), month(-1), day(-1) {}								// default constructor
	Date(int y, int m, int d) { year = y, month = m, day = d; }			// constructor
	
	// mutator of class Date	
	void setDate(int newYear, int newMonth, int newDay) { year = newYear, month = newMonth, day = newDay; }
	
	// accessor of class Date
	int getYear() const { return year; }
	int getYearDay() const;
	int getWeekDay() const;
	int getElapsedDays() const;											// get elapsed days from AD 1. 1. 1.
	
	// operator overloading
	Date operator=(const Date rightSide);
	bool operator>(Date rightSide) const;
	bool operator>=(Date rightSide)const;
	bool operator<(Date rightSide)const;
	bool operator<=(Date rightSide)const;
	bool operator==(Date rightSide)const;
	bool operator!=(Date rightSide)const;
	bool isLeapYear(int y);

private:
	bool isLeapYear() const;
	bool isLeapYear(int y) const;
	bool isValidDate(int y, int m, int d) const;
	int year;
	int month;
	int day;
};

#endif