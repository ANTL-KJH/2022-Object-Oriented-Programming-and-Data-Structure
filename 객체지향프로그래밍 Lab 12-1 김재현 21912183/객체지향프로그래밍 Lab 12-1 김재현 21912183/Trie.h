/*Trie.h*/
#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#include "TrieNode.h"
#define MAX_STR_LEN 50

using namespace std;

typedef list<MyVoca*> List_pVoca;
typedef list<MyVoca*>::iterator List_pVoca_Iter;
enum SearchMode { FULL_MATCH, PREFIX_MATCH };

template<typename E>
class Trie
{
public:
	// Constructor
	Trie(string name);

	// Accessor
	int size() { return num_keys; }

	void insert(string keyStr, E value); 
	void insertExternalTN(TrieNode<E>* pTN, string keyStr, E value); 
	TrieNode<E>* find(string keyStr); 
	void findPrefixMatch(string prefix, List_pVoca& predictWords); 
	void deleteKeyStr(string keyStr); 
	void eraseTrie(); 
	void fprintTrie(ostream& fout); 
protected:
	TrieNode<E>* _find(string keyStr, SearchMode sm = FULL_MATCH); 
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_keywords); 
	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent);
private:
	TrieNode<E>* _root; 
	int num_keys;
	string trie_name; 
};

template<typename E>
Trie<E>::Trie(string name)
{
	this->trie_name = name;
	this->_root = new TrieNode<E>('\0', NULL);
	this->_root->setKey('\0');		// set Key as NULL
	this->_root->setPrev(NULL);		// set prev node as NULL
	this->_root->setNext(NULL);		// set next node as NULL
	this->_root->setParent(NULL);	// set parent node as NULL
	this->_root->setChild(NULL);	// set child node as NULL
	this->num_keys = 0;
}

template<typename E>
void Trie<E>::insert(string keyStr, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char* keyPtr = (char*)keyStr.c_str();			// convert string to char*

	if (keyPtr == NULL)								// string doesn't exist
		return;

	if (_find(keyStr, FULL_MATCH) != NULL)			// keyStr's full match key word is not exist in trie
	{
		cout << "The given key string is already existing : " << keyStr << endl;
		return;										// just return
	}
	
	pTN = this->_root;								// setting pTN as root
	while ((pTN != NULL) && (*keyPtr != '\0'))		// When pTN is not NULL and Key is not NULL
	{
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))		// next node doesn't exist
			break;

		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL))						// next node exist
			pTN = pTN->getNext();					// move to next node

		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))			// find key
		{
			pTN = pTN->getChild();					// move to child node
			keyPtr++;								// next character
		}

		if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))			// reached
			break;
	}

	if ((pTN->getKey() != '\0') && (*keyPtr == '\0')) // insert value
	{
		pTN_New = new TrieNode<E>('\0', value);
		pTN_New->setParent(pTN->getParent());		// set Parent Node
		(pTN->getParent())->setChild(pTN_New);		// set Child Node
		pTN_New->setNext(pTN);						// set Next Node
		pTN->setPrev(pTN_New);						// set Prev Node
		this->num_keys++;
		return;
	}
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
	{
		
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setParent(pTN->getParent());		// set Parent Node
		pTN_New->setPrev(pTN);						// set Prev Node
		pTN->setNext(pTN_New);						// set Next Node
		pTN = pTN_New;								// Move to Next Node
		keyPtr++;									// next character
		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); //new node
			pTN->setChild(pTN_New);					// set new Child Node
			(pTN->getChild())->setParent(pTN);		// set Child Node's parent
			pTN = pTN->getChild();					// Move to Child
			keyPtr++;								// next character
		}
		if (*keyPtr == '\0')						// if reached last character ex) mean"\0"
		{
			insertExternalTN(pTN, keyStr, value);	// insert NULL Node
			this->num_keys++;						// increase size
			return;
		}
	}
	else if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setNext(pTN);						// set NewNode's NextNode
		pTN_New->setParent(pTN->getParent());		// set NewNode's ParentNode

		if (pTN->getPrev() == NULL)
		{
			if (pTN->getParent() != NULL)			
				(pTN->getParent())->setChild(pTN_New);	// set Child
		}
		else
			(pTN->getPrev())->setNext(pTN_New);		// pTN_New's position is between pTN and pTN->Prev
		pTN_New->setPrev(pTN->getPrev());			// set PrevNode
		pTN->setPrev(pTN_New);						// set PrevNode
		pTN = pTN_New;								// Move to NewNode
		keyPtr++;									// next character

		while (*keyPtr != '\0')						// if not last Character
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);	// new node
			pTN->setChild(pTN_New);					// set Child Node
			(pTN->getChild())->setParent(pTN);		// set Parent Node
			pTN = pTN->getChild();					// Move to Child
			keyPtr++;								// Next character
		}
		if (*keyPtr == '\0') //if reach end of keyStr
		{
			insertExternalTN(pTN, keyStr, value);	//add Null word next to last node
			this->num_keys++;						// increase size
			return;
		}
	}
}

template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keyStr, E value)	// insertExternalTN, insert NULL Node at last position
{
	TrieNode<E>* pTN_New; 
	pTN_New = new TrieNode<E>('\0', value);			// Dynamic Memrory Allocation, gen NULL TrieNode
	pTN->setChild(pTN_New);							// set Child Node
	(pTN->getChild())->setParent(pTN);				// set end Node's Parent
	pTN_New->setValue(value);
	//cout << "key (" << keyStr << ") is inserted \n";
}


template<typename E>
TrieNode<E>* Trie<E>::find(string keyStr)						// public member function find
{
	TrieNode<E>* pTN = NULL;

	pTN = _find(keyStr, FULL_MATCH);							// call private member function _find
	return pTN;
}

template<typename E>
TrieNode<E>* Trie<E>::_find(string keyStr, SearchMode sm)		// class Trie's private member function
{
	const char* keyPtr;
	TrieNode<E>* pTN = NULL;
	TrieNode<E>* found = NULL;
	if (keyStr.empty())											// if key string is NULL, return NULL
		return NULL;
	keyPtr = (char*)keyStr.c_str();								// convert string to char*
	pTN = this->_root;											// set pTN as ROOT
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		while ((pTN != NULL) && (pTN->getKey() < *keyPtr))
		{
			if (pTN->getNext() == NULL)
				return NULL;
			pTN = pTN->getNext();								// move to Next
		}
		if ((pTN != NULL) && (pTN->getKey() > *keyPtr))			
		{
			return NULL;
		}
		else if ((pTN == NULL) && (*keyPtr != '\0'))
		{
			return NULL;
		}
		else if ((pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))	// find Node
		{
			pTN = pTN->getChild();								// move to Child
			keyPtr++;											
			if (*keyPtr == '\0')
			{
				if (sm == FULL_MATCH)							// if Search Mode is FULL_MATCH
				{
					if (pTN->getKey() == '\0')					// if pTN is NULL
					{
						return pTN;
					}
					else
					{
						return NULL;
					}
				}
				else if (sm == PREFIX_MATCH)					// if Search Mode is PREFIX_MATCH
				{
					return pTN;
				}
			}
			else if ((pTN->getKey() == '\0') && (*keyPtr != '\0'))	// Node is NULL and keystring is not NULL
			{
				if (pTN->getNext() != NULL)						// if NextNode is NULL
				{
					pTN = pTN->getNext(); continue;				// move to Next
				}
				else
					return NULL;
			}
			else
			{
				continue;
			}
		}
	}

}

template<typename E>
void Trie<E>::findPrefixMatch(string prefix, List_pVoca& predictWords)		// Prefix Matching
{
	TrieNode<E>* pPtr = NULL;
	string keyPtr;
	TrieNode<E>* pTN = NULL;
	TrieNode<E>* found = NULL;
	keyPtr = prefix;
	if (prefix.empty())									// if prefix string is NULL, return
		return;
	pTN = this->_root;									// set pTN as ROOT
	pTN = _find(prefix, PREFIX_MATCH);					// find
	_traverse(pTN, predictWords);
}

template<typename E>
void Trie<E>::deleteKeyStr(string keyStr)
{
	TrieNode<E>* pTN = NULL, * _root;
	TrieNode<E>* tmp = NULL;
	int trie_val;
	_root = this->_root;								// set _root as ROOT
	if (NULL == _root || keyStr.empty())				// if root is NULL or Keystring is NULL
		return;
	pTN = _find(keyStr, FULL_MATCH);					// find FULL_MATCH KeyWord 
	if (pTN == NULL) {
		cout << "Key [" << keyStr << "] not found in trie" << endl;
		return;
	}
	while (1)
	{
		if (pTN == NULL)
			break;
		if (pTN->getPrev() && pTN->getNext())			// PrevNode, NextNode exist
		{
			tmp = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());	// Link NextNode to PrevNode
			(pTN->getPrev())->setNext(pTN->getNext());	// Link PrevNode to NextNode
			free(tmp);									// delete Node, free Memory
			break;
		}
		/*
			a							a
			b--c--n			=>			b--n
			c--t--t		delete act		c--t
		
		*/
		else if (pTN->getPrev() && !(pTN->getNext()))	// NextNode doesn't exist case
		{
			tmp = pTN;
			(pTN->getPrev())->setNext(NULL);			// set NextNode as NULL
			free(tmp);									// delete Node, free Memory
			break;
		}
		/*
			a							a
			b--c--n			=>			b--c
			c--t--t		delete ant		c--t

		*/
		else if (!(pTN->getPrev()) && pTN->getNext())	// PrevNode doesn't exist case
		{
			tmp = pTN;
			(pTN->getParent())->setChild(pTN->getNext());	// Link ParentNode to NextNode
			pTN = pTN->getNext();						// Move to Next Node
			pTN->setPrev(NULL);							// setPrev Node as NULL
			free(tmp);									// delete Node, free Memory
			break;
		}
		/*
			a							a
			b--c--n			=>			c--n
			c--t--t		delete abc		t--t

		*/
		else											// prevNode and NextNode doesn't exist
		{
			tmp = pTN;
			pTN = pTN->getParent();						// Move to Parent
			if (pTN != NULL) pTN->setChild(NULL);		// set ChildNode as NULL
			free(tmp);									// delete Node, free Memory
			if ((pTN == _root) && (pTN->getNext() == NULL) && (pTN->getPrev() == NULL))	// Only ROOT Node exist alone case
			{
				cout << "Now, the trie is empty !!" << endl;
				break;
			}
		}
	}
	this->num_keys--;
}

template<typename E>
void Trie<E>::eraseTrie()								// eraseTrie
{
	TrieNode<E>* pTN;
	TrieNode<E>* pTN_to_be_deleted = NULL;
	if (this->_root == NULL)							// Trie doesn't exist
		return;
	
	pTN = this->_root;									// set pTN as ROOT
	while (pTN != NULL)
	{
		while ((pTN != NULL) && (pTN->getNext()))		// Next Node exist
			pTN = pTN->getNext();						// Move to Next

		while (pTN->getChild())							// if has Child
		{
			if (pTN->getNext())							// if NextNode exist
				break;
			pTN = pTN->getChild();						// Move to ChildNode
		}
		if (pTN->getNext())								// if NextNode exist
			continue;
		if (pTN->getPrev() && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			pTN = pTN->getNext();						// Move to NextNode
			free(pTN_to_be_deleted);					// delete Node, free Memory
		}
		else if (pTN->getPrev() && !(pTN->getNext()))
		{
			pTN_to_be_deleted = pTN;
			(pTN->getPrev())->setNext(NULL);
			pTN = pTN->getPrev();
			free(pTN_to_be_deleted);					// delete Node, free Memory
		}
		else if (!(pTN->getPrev()) && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			(pTN->getNext())->setPrev(NULL);
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);					// delete Node, free Memory
		}
		else
		{
			pTN_to_be_deleted = pTN;
			if (pTN == this->_root)						// pTN is ROOT Node
			{
				this->num_keys = 0;
				return;
			}
			if (pTN->getParent() != NULL)				// pTN has Parent Node 
			{
				pTN = pTN->getParent();					// Move to Partent Node
				pTN->setChild(NULL);					// set Child Node as NULL
			}
			else
			{
				pTN = pTN->getPrev();					// Move to Prev Node
			}
			free(pTN_to_be_deleted);					// delete Node, free Memory
		}
	}

}

template<typename E>
void Trie<E>::fprintTrie(ostream& fout)					// printout Trie at file
{
	TrieNode<E>* pTN;
	int line = 1, indent = 0;
	fout << "trie ( " << this->trie_name << ") with " << this->num_keys << " trie_nodes\n";
	if (this->num_keys == 0)							// if trie is empty
	{
		fout << "Empty trie !" << endl;
		return;
	}
	pTN = this->_root;									// set pTN as ROOT
	pTN->_fprint(fout, pTN, indent);					// call private member function
}




template<typename E>
void Trie<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)									// pTN doesn't exist
	{
		fout << endl;
		return;
	}
	else
	{
		fout << pTN->key;								// printout key
		_fprint(fout, pTN->child, indent + 1);			// move to child, add indent, recursive
		if (pTN->next == NULL)							// end of same depth
			return;
		for (int i = 0; i < indent; i++)				// indent for Trie printout
			fout << " ";
		_fprint(fout, pTN->next, indent);				// move to NextNode and recursive
	}
}

template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, List_pVoca& list_keywords)		// traverse
{
	if (pTN == NULL)									// if pTN is NULL, return
		return;
	if (pTN->getChild() == NULL)						// Child doesn't exist
	{
		list_keywords.push_back(pTN->getValue());
	}
	else
	{
		_traverse(pTN->getChild(), list_keywords);		// recursive
	}
	if (pTN->getNext() != NULL)							// Next == NULL
	{
		_traverse(pTN->getNext(), list_keywords);		// recursive
	}
}

#endif