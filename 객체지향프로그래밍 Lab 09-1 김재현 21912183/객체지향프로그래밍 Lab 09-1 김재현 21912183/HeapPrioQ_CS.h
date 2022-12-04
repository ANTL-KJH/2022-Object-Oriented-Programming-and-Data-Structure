/*Class_HeapPriQ.h*/
#ifndef CLASS_HEAPPRIQ
#define CLASS_HEAPPRIQ
#include <iostream>
#include <string>
#include <mutex>
using namespace std;
#include "Class_CompleteBinaryTree.h"

template<typename K, typename V>
class HeapPrioQ_CS : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQ_CS(int capa, string nm);
	~HeapPrioQ_CS();
	bool isEmpty() { return size() == 0; }
	bool isFull() { return size() == this->capacity; }
	T_Entry<K, V>* insert(const T_Entry<K, V>& elem);
	T_Entry<K, V>* removeHeapMin();
	T_Entry<K, V>* getHeapMin();
	void fprint(ostream& fout);
	int size() { return this->end; }
private:
	int heapPriQ_capa;
	mutex cs_priQ;
};

template<typename K, typename V>
HeapPrioQ_CS<K, V>::HeapPrioQ_CS(int capa, string nm)					// constructor
	:CompleteBinaryTree<K, V>(capa, nm)
{
	heapPriQ_capa = capa;
}

template<typename K, typename V>
HeapPrioQ_CS<K, V>::~HeapPrioQ_CS()									// destructor
{

}

template<typename K, typename V>
void HeapPrioQ_CS<K, V>::fprint(ostream& fout)
{
	if (size() <= 0)													// check empty
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return;
	}
	else
		this->fprintCBT(fout);
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQ_CS<K, V>::insert(const T_Entry<K, V>& elem)
{
	int index, parent_index;
	T_Entry<K, V> temp;
	cs_priQ.lock();								// mutex lock for up heapbubbling
	if (isFull())
	{
		cout << "HeapPrioQ is Full !!" << endl;
		cs_priQ.unlock();						// return 하는 경우 unlock
		return NULL;
	}
	//cs_priQ.lock();
	index = this->add_at_end(elem);
	/* up-heap bubbling */
	while (index != CBT_ROOT)
	{
		parent_index = this->parentIndex(index);
		if (this->t_GA[index].getKey() >= this->t_GA[parent_index].getKey())
			break;
		else									// swap
		{
			temp = this->t_GA[index];
			this->t_GA[index] = this->t_GA[parent_index];
			this->t_GA[parent_index] = temp;
			index = parent_index;
		}
	}
	cs_priQ.unlock();							// mutex unlock

	T_Entry<K, V>* pRoot = &(this->t_GA[CBT_ROOT]);
	return pRoot;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQ_CS<K, V>::getHeapMin()						// get Min Data
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
T_Entry<K, V>* HeapPrioQ_CS<K, V>::removeHeapMin()
{
	int index_p, index_c, index_rc;
	T_Entry<K, V>* pMinElem;
	T_Entry<K, V> temp, t_p, t_c;
	//cs_priQ.lock();

	int HPQ_size = size();
	if (HPQ_size <= 0)													// empty check
	{
		
		//cs_priQ.unlock();
		cout << "remove unlock";
		return NULL;
	}
	cs_priQ.lock();
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

		while (this->hasLeftChild(index_p))							// down heap bubbling
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
	cs_priQ.unlock();												// mutex unlock
	return pMinElem;
}
#endif