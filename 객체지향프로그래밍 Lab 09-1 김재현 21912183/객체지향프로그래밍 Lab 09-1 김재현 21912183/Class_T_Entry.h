/*Class_T_Entry.h*/
#ifndef CLASS_T_ENTRY
#define CLASS_T_ENTRY
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

template<typename K, typename V>
class T_Entry
{
	friend ostream& operator<<(ostream& fout, T_Entry<K, V>& entry)
	{
		fout << " [Key:" << entry.getKey() << "]";
		return fout;
	}
public:
	T_Entry(K key, V value) { _key = key; _value = value; }
	T_Entry() { _key = 999; } // default constructor
	~T_Entry() {}
	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }
	K getKey() const { return _key; }
	V getValue() const { return _value; }
	bool operator>(const T_Entry& right) { return (_key > right.getKey()); }
	bool operator>=(const T_Entry& right) { return (_key >= right.getKey()); }
	bool operator<(const T_Entry& right) { return (_key < right.getKey()); }
	bool operator<=(const T_Entry& right) { return (_key <= right.getKey()); }
	bool operator==(const T_Entry& right) { return ((_key == right.getKey()) && (_value == right.getValue())); }
	T_Entry& operator=(const T_Entry& right);
	void fprint(ostream& fout);
private:
	K _key;
	V _value;
};

template<typename K, typename V>
void T_Entry<K, V>::fprint(ostream& fout)			// printout
{
	fout << "[Key:" << setw(2) << this->getKey() << ", " << *this->getValue() << "]";
}

template<typename K, typename V>
T_Entry<K, V>& T_Entry<K, V>::operator=(const T_Entry& right)		// operation overloading = assign
{
	this->_key = right._key;
	this->_value = right._value;
	return *this;
}
#endif