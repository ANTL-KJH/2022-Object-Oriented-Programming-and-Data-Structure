/*Class_HeapPriQ.h*/
#ifndef CLASS_HEAPPRIQ
#define CLASS_HEAPPRIQ
#include <iostream>
#include <string>
using namespace std;
#include "Class_CompleteBinaryTree.h"

template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQueue(int capa, string nm);
	~HeapPrioQueue();
	bool isEmpty() { return size() == 0; }
	bool isFull() { return size() == this->capacity; }
	int insert(T_Entry<K, V>& elem);
	T_Entry<K, V>* removeHeapMin();
	T_Entry<K, V>* getHeapMin();
	void fprint(ofstream& fout);
	int size() { return this->end; }
};

template<typename K, typename V>
HeapPrioQueue<K, V>::HeapPrioQueue(int capa, string nm)					// constructor
:CompleteBinaryTree<K, V>(capa, nm)
{

}

template<typename K, typename V>
HeapPrioQueue<K, V>::~HeapPrioQueue()									// destructor
{

}

template<typename K, typename V>
void HeapPrioQueue<K, V>::fprint(ofstream& fout)
{
	if (size() <= 0)													// check empty
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return;
	}
	else
		CompleteBinaryTree::printCBT(fout);
}

template<typename K, typename V>
int HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, parent_index;
	T_Entry<K, V> temp;
	if (isFull())														// check full
	{
		cout << this->getName() << " is Full !!" << endl;
		return size();
	}
	index = this->add_at_end(elem);

	while (index != CBT_ROOT)											// up heap bubbling
	{
		parent_index = this->parentIndex(index);
		if (this->t_GA[index].getKey() >= this->t_GA[parent_index].getKey())
			break;
		else
		{
			temp = this->t_GA[index];
			this->t_GA[index] = this->t_GA[parent_index];
			this->t_GA[parent_index] = temp;
			index = parent_index;
		}
	}
	return size();
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::getHeapMin()						// get Min Data
{
	T_Entry<K, V>* pMinElem;
	if (size() <= 0)
	{
		return NULL;
	}
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = this->getRootElement();
	return pMinElem;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::removeHeapMin()	
{
	int index_p, index_c, index_rc;
	T_Entry<K, V>* pMinElem;
	T_Entry<K, V> temp, t_p, t_c;
	int HPQ_size = size();
	if (HPQ_size <= 0)													// empty check
	{
		return NULL;
	}
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = this->getRootElement();
	if (HPQ_size == 1)
	{
		this->removeCBTEnd();
	}
	else
	{
		index_p = CBT_ROOT;
		this->t_GA[CBT_ROOT] = this->t_GA[this->end];
		this->end--;
								
		while (this->hasLeftChild(index_p))								// down heap bubbling
		{
			index_c = this->leftChildIndex(index_p);
			index_rc = this->rightChildIndex(index_p);
			if (this->hasRightChild(index_p) && (this->t_GA[index_c] > this->t_GA[index_rc]))
				index_c = index_rc;
			t_p = this->t_GA[index_p];
			t_c = this->t_GA[index_c];
			if (t_p > t_c)
			{
				temp = this->t_GA[index_p];
				this->t_GA[index_p] = this->t_GA[index_c];
				this->t_GA[index_c] = temp;
				index_p = index_c;
			}
			else
				break;
		}
	}
	return pMinElem;
}
#endif