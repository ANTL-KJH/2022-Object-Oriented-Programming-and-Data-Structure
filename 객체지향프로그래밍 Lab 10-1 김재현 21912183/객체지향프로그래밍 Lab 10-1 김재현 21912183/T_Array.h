/*T_Array.h*/
#ifndef T_ARRAY_H
#define T_ARRAY_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Book.h"

template<typename V>
class T_Array
{
public:
	// Constructor and Destructor
	T_Array(int n, string nm);
	~T_Array();

	string getName() { return name; }
	void reserve(int new_capacity);
	void insertBack(V element);
	int size() const { return num_elements; }
	bool isValidIndex(int i);
	V& operator[](int index) { return t_GA[index]; }
private:
	V* t_GA;
	int num_elements;
	int capacity;
	string name;
};

template<typename V>
T_Array<V>::T_Array(int new_capacity, string nm)		// constructor
{
	capacity = new_capacity;
	t_GA = (V*) new V[capacity];						// Dynamic Memory Allocation
	if (t_GA == NULL)									// Memory Allocation Check
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit(1);
	}
	num_elements = 0;
	name = nm;
}

template<typename V>
T_Array<V>::~T_Array()									// destructor
{
	if (t_GA != NULL)
		delete[] t_GA;									// return Dynamic Memory
}

template<typename V>
void T_Array<V>::reserve(int new_capacity)				// reserve capa
{
	if (capacity >= new_capacity)						// check capa
		return;

	V* t_newGA = (V*) new V[new_capacity];				// Dynamic Memory Allocation for New capa
	if (t_newGA == NULL)								// Memory Allocation check
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit(1);
	}
	// cout << this->getName() << " expands capacity to " << setw(3) << new_capacity << endl;

	for (int i = 0; i < num_elements; i++)
		t_newGA[i] = t_GA[i];							// Copy Data
	delete[] t_GA;										// return memory
	t_GA = t_newGA;
	capacity = new_capacity;
}

template<typename V>
bool T_Array<V>::isValidIndex(int index)				// Index Valid Check
{
	if ((index < 0) || (index >= capacity))				// Valid Range
		return false;
	else
		return true;
}

template<typename V>
void T_Array<V>::insertBack(V element)					// insert New data at the end
{
	if (num_elements >= capacity)						// check full
	{
		int new_capa;
		new_capa = ((2 * capacity) > 1) ? 2 * capacity : 1;
		reserve(new_capa);
	}

	if (isValidIndex(num_elements))						// Index Valid Check
	{
		t_GA[num_elements] = element;					// Insert New Data
		num_elements++;
	}
}

#endif