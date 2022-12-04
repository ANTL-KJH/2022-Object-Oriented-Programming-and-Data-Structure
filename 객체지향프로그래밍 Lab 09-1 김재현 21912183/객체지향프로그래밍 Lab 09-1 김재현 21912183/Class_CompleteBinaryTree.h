/*Class_CompleteBinaryTree.h*/
#ifndef CLASS_COMPLETEBINARYTREE
#define CLASS_COMPLETEBINARYTREE
#include <iostream>
using namespace std;
#define CBT_ROOT 1
#include "Class_TA_Entry.h"

template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V>			// inheritance TA_Entry
{
public:
	CompleteBinaryTree(int capa, string nm);
	~CompleteBinaryTree() {}
	int add_at_end(const T_Entry<K, V>& elem);
	T_Entry<K, V>& getEndElement() { return this->t_GA[end]; }
	T_Entry<K, V>& getRootElement() { return this->t_GA[CBT_ROOT]; }
	int getEndIndex() { return end; }
	void removeCBTEnd();
	void fprintCBT(ostream& fout);
	void fprintCBT_byLevel(ofstream& fout);
protected:
	void _printCBT_byLevel(ofstream& fout, int p, int level);
	int parentIndex(int index) { return index / 2; }
	int leftChildIndex(int index) { return index * 2; }
	int rightChildIndex(int index) { return (index * 2 + 1); }
	bool hasLeftChild(int index) { return ((index * 2) <= this->end); }
	bool hasRightChild(int index) { return ((index * 2 + 1) <= this->end); }
	int end;
};

template<typename K, typename V>
CompleteBinaryTree<K, V>::CompleteBinaryTree(int capa, string nm)			// constructor
	:TA_Entry<K, V>(capa, nm)
{
	this->end = 0;
}

template<typename K, typename V>
int CompleteBinaryTree<K, V>::add_at_end(const T_Entry<K, V>& elem)				// add data at the end
{

	if (this->end >= this->capacity)										// check full
	{
		cout << this->getName() << " is FULL now !!" << endl;
		return this->end;
	}
	this->end++;
	this->t_GA[this->end] = elem;
	return this->end;
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::removeCBTEnd()								// remove end
{
	this->end--;
	this->num_elements--;
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT(ostream& fout)					// printout CBT
{
	if (this->end <= 0)
	{
		fout << this->getName() << " is empty now !!" << endl;
		return;
	}
	int count = 1;
	for (int i = 1; i <= this->end; i++)
	{
		fout << this->t_GA[i];
		if (count == 5)
		{
			fout << endl;
			count = 0;
		}
		count++;
	}
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::_printCBT_byLevel(ofstream& fout, int index, int level)		// level 구분하여 출력
{
	int index_child;
	if (hasRightChild(index))											// 상단부에 RightChild 출력
	{
		index_child = this->rightChildIndex(index);
		_printCBT_byLevel(fout, index_child, level + 1);
	}
	for (int i = 0; i < level; i++)
		fout << "    ";
	this->t_GA[index].fprint(fout);
	fout << endl;
	if (this->hasLeftChild(index))										// 하단부에 LeftChild 출력
	{
		index_child = this->leftChildIndex(index);
		_printCBT_byLevel(fout, index_child, level + 1);
	}
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT_byLevel(ofstream& fout)
{
	if (end <= 0)														// check empty
	{
		fout << "CBT is EMPTY now !!" << endl;
		return;
	}
	_printCBT_byLevel(fout, CBT_ROOT, 0);								// call _printCBT_byLevel
}

#endif