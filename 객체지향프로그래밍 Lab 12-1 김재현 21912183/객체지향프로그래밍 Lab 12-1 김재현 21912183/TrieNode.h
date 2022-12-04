/*TrieNode.h*/
#ifndef TRIE_NODE_H
#define TRIE_NODE_H
#include <iostream>
#include <list>
#include "MyVoca.h"

#define VALUE_INTERNAL_NODE NULL
using namespace std;
typedef list<string>STL_list;

template <typename E>
class TrieNode
{
public:
	// Constructor
	TrieNode() {}
	TrieNode(char k, E v) :key(k), value(v) { prev = next = parent = child = NULL; } 
	// Mutator
	void setKey(char k) { key = k; }
	void setValue(E v) { value = v; }
	void setNext(TrieNode<E>* next) { this->next = next; }
	void setPrev(TrieNode<E>* prev) { this->prev = prev; }
	void setParent(TrieNode<E>* parent) { this->parent = parent; }
	void setChild(TrieNode<E>* child) { this->child = child; }

	// Accessor
	char getKey() { return key; }
	E getValue() { return value; }
	TrieNode<E>* getPrev() { return prev; }
	TrieNode<E>* getNext() { return next; }
	TrieNode<E>* getParent() { return parent; }
	TrieNode<E>* getChild() { return child; }

	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent); //fprinting inner function

private:
	char key;			
	E value;			
	TrieNode<E>* prev;	
	TrieNode<E>* next;	
	TrieNode<E>* parent;
	TrieNode<E>* child; 
};

template <typename E>
void TrieNode<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)					// Trie Node is not existing
	{
		fout << endl;
		return;
	}
	else
	{
		fout << pTN->key;
		_fprint(fout, pTN->child, indent + 1);	// recursive
		if (pTN->next == NULL)					// end of same level Node
			return;
		for (int i = 0; i < indent; i++)
			fout << " ";
		_fprint(fout, pTN->next, indent);		// recursive
	}
}

#endif