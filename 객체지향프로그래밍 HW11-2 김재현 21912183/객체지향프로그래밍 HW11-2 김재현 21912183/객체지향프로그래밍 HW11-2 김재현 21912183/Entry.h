/* Entry.h */
#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
using namespace std;

template<typename K, typename V>
class Entry
{
	friend ostream& operator<<(ostream& fout, Entry<K, V>& entry)
	{
		fout << "KEY : " << entry.getKey() << ", Value :" << entry.getValue();
		return fout;
	}
public:
	// constructor and destructor
	Entry(K key, V value) : _key(key), _value(value) {}
	Entry() {}
	~Entry() {}

	// mutator and accessor
	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }
	K getKey() const { return _key; }
	V getValue() const { return _value; }

	// operator overloading
	bool operator>(const Entry<K, V>& right) const { return (_key > right.getKey()); }
	bool operator>=(const Entry<K, V>& right) const { return (_key >= right.getKey()); }
	bool operator<(const Entry<K, V>& right) const { return (_key < right.getKey()); }
	bool operator<=(const Entry<K, V>& right) const { return (_key <= right.getKey()); }
	bool operator==(const Entry<K, V>& right) const
	{
		return ((_key == right.getKey()) && (_value == right.getValue()));
	}
	Entry<K, V>& operator=(Entry<K, V>& right);

	// printout
	void fprint(ostream fout);
private:
	K _key;
	V _value;
};

template<typename K, typename V>
Entry<K, V>& Entry<K, V>::operator=(Entry<K, V>& right)				// operator overloading =, assign
{
	this->_key = right._key;
	this->_value = right._value;
	return *this;
}

template<typename K, typename V>
void Entry<K, V>::fprint(ostream fout)								// printout
{
	fout << "KEY : " << this->_key << ", Value :" << this->_value;
}
#endif