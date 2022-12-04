/*Class_TA_Entry*/
#ifndef Class_TA_Entry
#define Class_TA_Entry

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "Class_T_Entry.h"

enum SortingDirection { INCREASING, DECREASING };

template<typename K, typename V>
class TA_Entry
{
public:
	TA_Entry(int n, string nm);							// constructor
	~TA_Entry();										// destructor
	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return name; }
	void reserve(int new_capacity);
	void insert(int i, T_Entry<K, V> element);
	void remove(int i);
	T_Entry<K, V>& at(int i);
	void set(int i, T_Entry<K, V>& element);
	T_Entry<K, V> getMin(int begin, int end);
	T_Entry<K, V> getMax(int begin, int end);
	void shuffle();
	int sequential_search(T_Entry<K, V> search_key);
	int binary_search(T_Entry<K, V> search_key);
	void selection_sort(SortingDirection sd);
	void quick_sort(SortingDirection sd);
	void fprint(ofstream& fout, int elements_per_line);
	void fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines);
	bool isValidIndex(int i);
	T_Entry<K, V>& operator[](int index) { return t_GA[index]; }
protected:
	T_Entry<K, V>* t_GA;
	int num_elements;
	int capacity;
	string name;
};

template<typename K, typename V>
TA_Entry<K, V>::TA_Entry(int n, string nm)		// constructor
{
	capacity = n;
	name = nm;
	t_GA = new T_Entry<K, V>[capacity+1];			// dynamic memory allocation
	//t_GA = (T_Entry<K, V>*)calloc(capacity, sizeof(T_Entry<K, V>));
}

template<typename K, typename V>
TA_Entry<K, V>::~TA_Entry()						// destructor
{
	//delete &t_GA;
}

template<typename K, typename V>
void TA_Entry<K, V>::reserve(int new_capacity)
{
	if (capacity >= new_capacity)
		return;

	T_Entry<K, V>* old_array = this->t_GA;
	this->t_GA = new T_Entry<K, V>[new_capacity];				// dynamic memory allocation
	if (t_GA == NULL)
	{
		cout << "Error in allocate array !!" << endl;
		exit(-1);
	}
	cout << name << " expands capacity to " << new_capacity << endl;
	for (int i = 0; i < this->num_elements; i++)
		t_GA[i] = old_array[i];

	delete[] old_array;											// free dynamic memory
	capacity = new_capacity;
}

template<typename K, typename V>
void TA_Entry<K, V>::insert(int i, T_Entry<K, V> element)
{
	if (this->num_elements >= this->capacity)					// check full
	{
		cout << "ERROR : NO MORE MEMORY" << endl;
		exit(0);
	}
	if (this->isValidIndex(i))									// index valid check
	{
		for (int j = this->num_elements - 1; j >= i; j--)
			this->t_GA[j + 1] = this->t_GA[j];					// shift up the position of data
		this->t_GA[i] = element;								// insert
		this->num_elements++;
	}
}

template<typename K, typename V>
void TA_Entry<K, V>::remove(int i)								// remove data
{
	delete this->t_GA[i];
}

template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>::at(int i)						// return index data
{
	return this->t_GA[i];
}

template<typename K, typename V>
void TA_Entry<K, V>::set(int i, T_Entry<K, V>& element)			// set data
{
	this->t_GA[i] = element;
}

template<typename K, typename V>
T_Entry<K, V> TA_Entry<K, V>::getMin(int begin, int end)		// get Min Data
{
	int minIndex = begin;

	for (int i = begin + 1; i < end; i++)						// search min data
	{
		if (this->t_GA[i] < this->t_GA[minIndex])
			minIndex = i;										// new Min index
	}
	return this->t_GA[minIndex];
}

template<typename K, typename V>
T_Entry<K, V> TA_Entry<K, V>::getMax(int begin, int end)		// get Max Data
{
	int maxIndex = begin;

	for (int i = begin + 1; i < end; i++)						//search max data
	{
		if (this->t_GA[i] > this->t_GA[maxIndex])
			maxIndex = i;										// new Max Index
	}
	return this->t_GA[maxIndex];
}

template<typename K, typename V>
void TA_Entry<K, V>::shuffle()
{
	srand(time(NULL));
	int index1, index2;
	int rand_1, rand_2;
	K temp;
	for (int i = 0; i < num_elements; i++)
	{
		rand_1 = rand();
		rand_2 = rand();
		index1 = ((rand_1 << 15) | rand_2) & num_elements;		// idx1
		rand_1 = rand();
		rand_2 = rand();
		index2 = ((rand_1) << 15 | rand_2) & num_elements;		// idx2
		temp = t_GA[index1];
		t_GA[index1] = t_GA[index2];
		t_GA[index2] = temp;
	}
}

template<typename K, typename V>
int TA_Entry<K, V>::sequential_search(T_Entry<K, V> search_key)
{
	int index = 0;
	for (int index = 0; index < this->num_elements; index++)
	{
		if (this->t_GA[index] == search_key)					// if find search_key, return index
			return index;
	}
	return -1;													// can't find
}

template<typename K, typename V>
int TA_Entry<K, V>::binary_search(T_Entry<K, V> search_key)
{
	int low, mid, high;
	int loop = 1;
	low = 0;
	high = this->num_elements - 1;
	while (low <= high)
	{
		cout << setw(2) << loop << "-th loop: current search range [" << setw(3)
			<< low << ", " << setw(3) << high << "]" << endl;

		mid = (low + high) / 2;
		if (this->t_GA[mid] == search_key)						// check mind
			return mid;
		else if (this->t_GA[mid] > search_key)					// mid value > key
			high = mid - 1;										// new range
		else
			low = mid + 1;										// new range
		loop++;
	}
	return -1;													// can't find
}

template<typename K, typename V>
void TA_Entry<K, V>::selection_sort(SortingDirection sd)
{
	int maxIndex, minIndex;
	V temp;

	K compareKey;
	K key;

	for (int i = 0; i < this->num_elements - 1; i++)
	{
		if (sd == INCREASING)									// SortingDirection == INCREASING
		{
			minIndex = i;
			this->t_GA[i]->getKey();
			compareKey = (K)key;								// 비교 기준 key
			for (int j = i + 1; j < this->num_elements; j++)
			{
				this->t_GA[j]->getKey();
				if (key < compareKey)							// compare
				{
					minIndex = j;
					compareKey = (K)key;
				}
			}
			if (minIndex != i)									// swap
			{
				temp = this->t_GA[minIndex];
				this->t_GA[minIndex] = this->t_GA[i];
				this->t_GA[i] = temp;
			}
		}
		else													// SortingDirection == Decreasing
		{
			maxIndex = i;
			this->t_GA[i]->getKye();
			compareKey = (K)key;
			for (int j = i + 1; j < this->num_elements; j++)
			{
				this->t_GA[j]->getKey();
				if (key > compareKey)							// compare
				{
					maxIndex = j;
					compareKey = (K)key;
				}
			}
			if (maxIndex != i) 									// swap
			{
				temp = this->t_GA[maxIndex];
				this->t_GA[maxIndex] = this->t_GA[i];
				this->t_GA[i] = temp;
			}
		}
	}
}

template<typename K, typename V>
void _partition(V* array, int size, int left, int right, int pivotIndex, SortingDirection sd)			// partition
{
	V pivotValue, temp;
	int newPI;

	pivotValue = array[pivotIndex];							// 중앙값, (left + right) / 2
	array[pivotIndex] = array[right];
	array[right] = pivotValue;
	newPI = left;

	for (int i = left; i <= (right - 1); i++)
	{
		if (sd == INCREASING)								// SortingOrder == INCREASING
		{
			if (array[i] <= pivotValue)						// swap
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;
				newPI = newPI + 1;
			}
		}
		else												// SortingOrder == DECREASING
		{
			if (array[i] > pivotValue)						// swap
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp;
				newPI = newPI + 1;
			}
		}
		temp = array[newPI];
		array[newPI] = array[right];
		array[right] = temp;
		return newPI;
	}
}

template<typename K, typename V>
void _quick_sort(K* array, int size, int left, int right, SortingDirection sd)
{
	int pI, newPI;
	if (left >= right)
	{
		return;
	}
	else
	{
		pI = (left + right) / 2;								// find mid pos
	}

	newPI = _partition(array, size, left, right, pI, sd);		// partition

	if (left < (newPI - 1))										// left side
	{
		_quick_sort(array, size, left, newPI - 1, sd);
	}
	if ((newPI + 1) < right)									// right side 
	{
		_quick_sort(array, size, newPI + 1, right, sd);
	}
}

template<typename K, typename V>
void TA_Entry<K, V>::quick_sort(SortingDirection sd)
{
	_quick_sort(this->t_GA, this->num_elements, 0, this->num_elements - 1, sd);			// call _quick_sort
}


template<typename K, typename V>
void TA_Entry<K, V>::fprint(ofstream& fout, int elements_per_line)
{

}

template<typename K, typename V>
void TA_Entry<K, V>::fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines)
{

}

template<typename K, typename V>
bool TA_Entry<K, V>::isValidIndex(int i)
{
	if (i < 0 || this->index >= this->capacity)
		return false;
	else
		return true;
}
#endif