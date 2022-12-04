/*Class_T_Array.h*/
#ifndef T_Array_H
#define T_Array_H
#include <iostream>
#include <iomanip>
#include "Student.h"
using namespace std;
enum SortingOrder { INCREASING, DECREASING };

template<typename T, typename K>
class T_Array
{
public:
	T_Array(int n, string nm);							// constructor
	~T_Array();											// destructor
	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return name; }
	void reserve(int new_capacity);
	void insert(int i, T element);
	void selection_sort(string keyName, SortingOrder sortOrder);
	void merge_sort(string keyName, SortingOrder sortOrder);
	void print(int elements_per_line);
	bool isValidIndex(int i);
	bool isValidIndex_Insert(int i);
	T& operator[](int index) { return t_array[index]; }
private:
	void _mergeSort(T* arr, T* tmp_array, int left, int right, string keyName, SortingOrder sortOrder);
	T* t_array;
	int num_elements;
	int capacity;
	string name;
};

template<typename T, typename K>
T_Array<T, K>::T_Array(int new_capacity, string nm)			// constructor
{
	capacity = new_capacity;
	t_array = (T*) new T[capacity];
	if (t_array == NULL)
	{
		cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
		exit;
	}
	num_elements = 0;
	name = nm;
}

template<typename T, typename K>
T_Array<T, K>::~T_Array()								// destructor
{
	if (t_array != NULL)
		delete[] t_array;
}

template<typename T, typename K>
void T_Array<T, K>::reserve(int new_capacity)			// capacity check
{

	if (capacity >= new_capacity)
		return;

	T* old_array = this->t_array;
	this->t_array = new T[new_capacity];				// dynamic memory allocation
	if (t_array == NULL)
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	cout << name << " expands capacity to " << new_capacity << endl;

	for (int i = 0; i < this->num_elements; i++)
		t_array[i] = old_array[i];

	delete[] old_array;
	capacity = new_capacity;
}

template<typename T, typename K>
bool T_Array<T, K>::isValidIndex(int index)				// index 유효성 검사
{
	if ((index < 0) || (index >= num_elements))
		return false;
	else
		return true;
}

template<typename T, typename K>
bool T_Array<T, K>::isValidIndex_Insert(int index)		// index 유효성 검사, insert에서 사용
{
	if ((index < 0) || (index > num_elements))
		return false;
	else
		return true;
}

template<typename T, typename K>
void T_Array<T, K>::insert(int i, T new_element)		// insert data
{
	if (num_elements >= capacity)				// capacity check
	{
		int new_capa;
		new_capa = ((2 * capacity) > 1) ? 2 * capacity : 1;
		reserve(new_capa);
	}
	if (isValidIndex_Insert(i))					// index check
	{
		for (int j = num_elements - 1; j >= i; j--)
			t_array[j + 1] = t_array[j];
		t_array[i] = new_element;
		num_elements++;
	}
}


template<typename T, typename K>
void T_Array<T, K>::selection_sort(string keyName, SortingOrder sortOrder)
{
	int maxIndex, minIndex;
	T temp;
	K minVal;
	K maxVal;
	K key;
	for (int i = 0; i < this->num_elements - 1; i++)
	{
		if (sortOrder == INCREASING)						// SortOrder = INCREASING
		{
			minIndex = i;
			this->t_array[i]->getKey(keyName, &key);
			minVal = (K)key;								// setting  min index (conversion key type)
			for (int j = i + 1; j < this->num_elements; j++)
			{
				this->t_array[j]->getKey(keyName, &key);
				if ((K)key < minVal)
				{
					minIndex = j;
					minVal = (K)key;						// min index
				}
			}
			if (minIndex != i)								// swap
			{
				temp = this->t_array[minIndex];
				this->t_array[minIndex] = this->t_array[i];
				this->t_array[i] = temp;
			}
		}
		else												// SortOrder = DECREASING
		{
			maxIndex = i;
			this->t_array[i]->getKey(keyName, &key);
			maxVal = (K)key;
			for (int j = i + 1; j < this->num_elements; j++)
			{
				this->t_array[j]->getKey(keyName, &key);	//get each index data
				if ((K)key > maxVal)
				{
					maxIndex = j;
					maxVal = (K)key;						// max index
				}
			}
			if (maxIndex != i)								// swap
			{
				temp = this->t_array[maxIndex];
				this->t_array[maxIndex] = this->t_array[i];
				this->t_array[i] = temp;
			}
		}
	}
}

template<typename T, typename K>
void T_Array<T, K>::merge_sort(string keyName, SortingOrder order)		// merge sort
{
	T* tmp_array = new T[num_elements];
	if (tmp_array == NULL)
	{
		cout << "ERROR::Memory Allocation Error!!" << endl;
		exit(-1);
	}

	_mergeSort(t_array, tmp_array, 0, size() - 1, keyName, order);
	delete[] tmp_array;
}

template<typename T, typename K>
void T_Array<T, K>::print(int elements_per_line)			// printout data
{
	int count = 0;
	while (count < num_elements)
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			cout << *t_array[count] << " ";					// printout
			count++;
			if (count % elements_per_line == 0)
				cout << endl;
		}
	}
	cout << endl;
}

template<typename T, typename K>
inline void T_Array<T, K>::_mergeSort(T* arr, T* tmp_array, int left, int right, string KeyName, SortingOrder order)
{
	K key_i, key_j;

	if (left >= right)
		return;

	int mid = (left + right) / 2;
	_mergeSort(arr, tmp_array, left, mid, KeyName, order);				// call _mergesort
	_mergeSort(arr, tmp_array, mid + 1, right, KeyName, order);			// call _mergesort

	for (int i = left; i <= mid; i++)
		tmp_array[i] = arr[i];
	for (int j = 1; j <= right - mid; j++)
		tmp_array[right - j + 1] = arr[j + mid];

	for (int i = left, j = right, k = left; k <= right; k++)
	{
		tmp_array[i]->getKey(KeyName, &key_i);
		tmp_array[j]->getKey(KeyName, &key_j);
		if (order == INCREASING)										// Sortorder = INCREASING
		{
			if ((K)key_i < (K)key_j)
				arr[k] = tmp_array[i++];
			else
				arr[k] = tmp_array[j--];
		}
		else															// Sortorder = DECREASING
		{
			if ((K)key_i > (K)key_j)
				arr[k] = tmp_array[i++];
			else
				arr[k] = tmp_array[j--];
		}
	}

}

#endif