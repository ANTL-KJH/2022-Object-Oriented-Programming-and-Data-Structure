/* Date.h */
#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;
#define WEEKDAY_AD01Jan01 MON // the weekday of AD Jan 1.
#define DAYS_PER_WEEK 7
#define Secs_in_Minute 60
#define Secs_in_Hour (Secs_in_Minute * 60)
#define Secs_in_DAY (Secs_in_Hour * 24)
#define LOCAL_GMT_OFFSET_HOUR 9
class Date
{
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor
	~Date(); // destructor
	void inputDate();
	void fprintDate(ostream& fout);
	void setDate(int y, int m, int dy);
	void setRandDateAttributes();		// Random Date generator
	void setMonth(int m);
	void setYear(int y);
	int getYear() { return year; }
	int getMonth() { return month; } //Returns 1 for January, 2 for February, etc.
	int getDay() { return day; }
	int getYearDay();
	int getYearDay(int m, int d);
	int getWeekDay();
	int getElapsedDaysFromAD010101(Date d); // get elapsed days from AD 1. 1. 1.
	int getElapsedDaysFromAD010101();
private:
	bool isLeapYear(); // check whether the year is leap year
	bool isLeapYear(int y); // check whether the given year y is leap year
	bool isValidDate(int y, int m, int d);
	int year;
	int month;
	int day;
};
#endif