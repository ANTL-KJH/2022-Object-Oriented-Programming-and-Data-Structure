/*T_Entry.h*/
#ifndef T_Entry_H
#define T_Entry_H

#include <iostream>
using namespace std;

template<typename K, typename V>
class T_Entry
{
	friend ostream& operator<<(ostream& fout, T_Entry<K, V>& entry)
	{
		if (entry.getValue() != NULL)
			fout << "(" << setw(8) << entry.getKey() << ": " << *(entry.getValue()) << ")";
		return fout;
	}
public:
	// Constructor and Destructor
	T_Entry() {}
	T_Entry(K key, V value) { _key = key; _value = value; }
	~T_Entry() {}
	
	// Mutator of template T_Entry
	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }

	// Accessor of template T_Entry
	K getKey() const { return _key; }
	V getValue() const { return _value; }
	
	// operator overloading
	bool operator>(const T_Entry<K, V>& right) const { return (_key > right.getKey()); }
	bool operator>=(const T_Entry<K, V>& right) const { return (_key >= right.getKey()); }
	bool operator<(const T_Entry<K, V>& right) const { return (_key < right.getKey()); }
	bool operator<=(const T_Entry<K, V>& right) const { return (_key <= right.getKey()); }
	bool operator==(const T_Entry<K, V>& right) const { return ((_key == right.getKey()) && (_value == right.getValue())); }
	T_Entry<K, V>& operator=(T_Entry<K, V>& right);

private:
	K _key;
	V _value;
};

template<typename K, typename V>
T_Entry<K, V>& T_Entry<K, V>::operator=(T_Entry<K, V>& right)
{
	this->_key = right.getKey();
	this->_value = right.getValue();
	return *this;
}

#endif