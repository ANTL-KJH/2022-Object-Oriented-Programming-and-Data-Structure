/*Person.h*/
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;
class Person
{
	friend ostream& operator<< (ostream& fout, const Person& p);
public:
	Person() { name = "nobody", regID = 0 , nation = "NONE"; }
	Person(string n) { name = n, regID = 0, nation = "NONE"; }
	Person(string n, int ID, string country) { name = n, regID = ID, nation = country; }
	void set_name(string n) { name = n; }
	const string get_name() const { return name; }
	void set_nation(string country) { nation = country; }
	const string get_nation() const { return nation; }
	void set_regID(int rgID) { regID = rgID; }
	const int get_regID() const { return regID; }
protected:
	string name;
	int regID;
	string nation;
};
#endif