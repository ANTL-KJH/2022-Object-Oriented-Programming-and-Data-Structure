/*T_BST.h*/
#ifndef T_BST_H
#define T_BST_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include "T_BSTN.h"
#include "T_Entry.h"
#include "T_Array.h"
using namespace std;


template<typename K, typename V>
class T_BST
{
public:
	T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {}		// constructor
	string getName() { return name; }
	int size() const { return num_entry; }
	bool empty() const { return num_entry == 0; }
	void clear();
	
	// Accessor of Template T_BST
	T_BSTN<K, V>* getRoot() { return _root; }
	T_BSTN<K, V>** getRootAddr() { return &_root; }
	T_Entry<K, V>& getRootEntry() { return _root->getEntry(); }

	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp);

	// Insert
	void insertInOrder(const T_Entry<K, V> entry);
	void insertAndRebalance(T_Entry<K, V> e);

	// Tree Traversal
	void traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);
	void traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	void traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);

	// search value
	T_BSTN<K, V>* searchBSTN(K k);
	T_Entry<K, V>& minEntry();
	T_Entry<K, V>& maxEntry();

	// printout
	void fprint_with_Depth(ostream& fout);
	void fprint_inOrder(ostream& fout);
protected:
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot);
	T_BSTN<K, V>* _insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e);
	T_BSTN<K, V>* _insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e);

	// Rotate
	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot);

	int _getHeight(T_BSTN<K, V>* pTN);
	int _getHeightDiff(T_BSTN<K, V>* pTN);
	T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN);
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);
	void _fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth);
	void _fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout);
private:
	T_BSTN<K, V>* _root;		// root address
	int num_entry;				// number of tree nodes
	string name;
};


template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertInOrder(T_BSTN<K, V>** pp, T_BSTN<K, V>* parenPos, const T_Entry<K, V> entry)
{
	T_BSTN<K, V>* newPos, ** pChildPos;
	T_BSTN<K, V>* pos;
	T_Entry<K, V> ent;
	if (pp == NULL)									// if pp is null data
	{
		cout << "Error in creation of BinarySearchTree :";
		cout << "address of the pointer to the Root Node is NULL !!\n";
		exit(1);
	}
	pos = *pp;										// pp is root node
	if (pos == NULL)								// Root node is not exist
	{
		pos = new T_BSTN<K, V>(entry);
		if (parenPos == NULL)
		{
			_root = pos;							// initialize the root node
		}
		pos->setpPr(parenPos);
		*pp = pos;
		num_entry++;								// increment elements before insert
		return pos;
	}
	ent = pos->getEntry();

	// left is smaller value in Binary Search Tree
	if (entry < ent)								// compare Key value, entry's key is smaller than ent value
	{
		pChildPos = pos->getppLc();
		newPos = _insertInOrder(pChildPos, pos, entry);
		if (newPos != NULL)
			pos->setpLc(newPos);
		return NULL;
	}
	else if (entry >= ent)							// compare Key value, entry's key is bigger than ent value
	{
		pChildPos = pos->getppRc();
		newPos = _insertInOrder(pChildPos, pos, entry);
		if (newPos != NULL)
			pos->setpRc(newPos);
		return NULL;
	}
}

template<typename K, typename V>
void T_BST<K, V>::insertInOrder(const T_Entry<K, V> entry)		// insert
{
	_insertInOrder(&_root, NULL, entry);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_inOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)			// traversal(순회) in order, Lchild -> Parent -> Rchild
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();						// left child address
	pRc = pos->getpRc();						// righ child address
	traversal_inOrder(pLc, array_value);
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);				// value input at the array
	traversal_inOrder(pRc, array_value);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)		// Preorder traversal(전위 순회), parent -> Lchild -> Rchild
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;

	pLc = pos->getpLc();						// left child address
	pRc = pos->getpRc();						// right child address
	entry = pos->getEntry();					
	value = entry.getValue();
	array_value.insertBack(value);				// value input at the array
	traversal_preOrder(pLc, array_value);
	traversal_preOrder(pRc, array_value);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_postOrder(T_BSTN<K, V>*	pos, T_Array<V>& array_value)		// PostOrder Traversal(후위 순회), Lchild -> Rchild -> parent
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();						// left child address
	pRc = pos->getpRc();						// right child address
	traversal_postOrder(pLc, array_value);
	traversal_postOrder(pRc, array_value);
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);				// value input at the array
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_searchBSTN(T_BSTN<K, V>* pos, K k)
{
	K ent_k;
	T_BSTN<K, V>* pos_result = NULL;
	if (pos == NULL)
		return NULL;
	ent_k = pos->getKey();
	if (ent_k == k)								// find
		pos_result = pos;
	else if (ent_k > k)							// value > key
		pos_result = _searchBSTN(pos->getpLc(), k);
	else if (ent_k < k)							// value < key
		pos_result = _searchBSTN(pos->getpRc(), k);
		return pos_result;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::searchBSTN(K key)
{
	T_BSTN<K, V>* pEntry;
	pEntry = _searchBSTN(_root, key);			// start position is root
	return pEntry;
}


template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)		// find min value in BST
{
	T_BSTN<K, V>* pos, * pLc;
	if ((subRoot == NULL) || (NULL == subRoot->getpLc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpLc()) != NULL)								// last left child is smallest value
		pos = pos->getpLc();
	return pos;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)		// find max value in BST
{
	T_BSTN<K, V>* pos, * pLc;
	if ((subRoot == NULL) || (NULL == subRoot->getpRc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpRc()) != NULL)								// last right child is biggest value	
		pos = pos->getpRc();
	return pos;
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::minEntry()							// get min Entry
{
	T_BSTN<K, V>* pMin;
	pMin = _minBSTN(_root);										// find min value in BST					
	return pMin->getEntry();
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::maxEntry()							// get max Entry
{
	T_BSTN<K, V>* pMax;
	pMax = _maxBSTN(_root);										// find max value in BST	
	return pMax->getEntry();
}

template<typename K, typename V>
void T_BST<K, V>::_fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout)			// print out inOrder, LC -> Node -> RC
{
	T_BSTN<K, V>* pRc, * pLc;
	if ((pLc = pTN->getpLc()) != NULL)			// print out LC
		_fprint_inOrder(pLc, fout);
	fout << pTN->getEntry() << endl;			// print out Node
	if ((pRc = pTN->getpRc()) != NULL)			// print out RC
		_fprint_inOrder(pRc, fout);
}

template<typename K, typename V>
void T_BST<K, V>::fprint_inOrder(ostream& fout)				// print out inOrder, LC -> Node -> RC
{
	T_BSTN<K, V>* root = getRoot();
	if (num_entry == 0)										// check entry
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	_fprint_inOrder(root, fout);
}

template<typename K, typename V>
void T_BST<K, V>::_fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth)	// print out with Depth, RC -> Node -> LC
{
	T_BSTN<K, V>* pRc, * pLc;
	T_Entry<K, V>* pEntry;
	if ((pRc = pTN->getpRc()) != NULL)						// Right child exist
		_fprint_with_Depth(pRc, fout, depth + 1);			// print out Right child Node
	for (int i = 0; i < depth; i++)
	{
		fout << "    ";
	}
	fout << pTN->getEntry() << endl;						// print out Node
	if ((pLc = pTN->getpLc()) != NULL)						// Left child exist
		_fprint_with_Depth(pLc, fout, depth + 1);			// print out Left child Node
}

template<typename K, typename V>
void T_BST<K, V>::fprint_with_Depth(ostream& fout)			// print out with Depth, RC -> Node -> LC
{
	T_BSTN<K, V>* root = getRoot();
	if (num_entry == 0)										// check entry
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	_fprint_with_Depth(root, fout, 0);
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pptoBeErased)					// erase Binary Search Tree Node
{
	T_BSTN<K, V>* newSubRoot, * temp, * w, * wlc;
	T_BSTN<K, V>* toBeErased;
	toBeErased = *pptoBeErased;
	if (toBeErased == NULL)		// Node doesn't exist
		return NULL;
	if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() == NULL))			// doesn't have child Node
	{
		newSubRoot = NULL;
	}
	else if ((toBeErased->getpLc() != NULL) && (toBeErased->getpRc() == NULL))		// has only left child
	{
		newSubRoot = toBeErased->getpLc();											// Left child address
		newSubRoot->setpPr(toBeErased->getpPr());									// Link Node's Child to Node's Parent
	}
	else if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() != NULL))		// has only right child
	{
		newSubRoot = toBeErased->getpRc();											// Right child address
		newSubRoot->setpPr(toBeErased->getpPr());									// Link Node's Child to Node's Parent
	}
	else																			// has both child
	{
		int heightDiff = _getHeightDiff(toBeErased);								// Difference of LC and RC
		//T_BSTN<K, V>* parDel = toBeErased->getpPr();
		T_BSTN<K, V>* lChild = toBeErased->getpLc();								// Node's Left child
		T_BSTN<K, V>* rChild = toBeErased->getpRc();								// Node's Right child
		T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs;
		T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd;
		if (heightDiff > 0)															// Left child is higher than righr child
		{
			ioPd = _maxBSTN(lChild);												// in-order predecessor (ioPd), Left child Node's Max value
			lcIoPd = ioPd->getpLc();												// LC ioPd's left child	address
			parIoPd = ioPd->getpPr();												// LC ioPd's parent address
			newSubRoot = ioPd;														
			if (ioPd->getpPr() != toBeErased)										// LC ioPd's parent is toBeErased Node
			{																		
				newSubRoot->setpLc(lChild);											// new subRoot's Lc is toBeErased's LC
				parIoPd->setpRc(lcIoPd);											
				if (lcIoPd != NULL)													// If ioPd's left cild's isn't NULL
					lcIoPd->setpPr(parIoPd);										// ioPd's left child parent Node is changed ioPd's parent Node
			}
			newSubRoot->setpRc(rChild);												// link toBeErased's right child
			newSubRoot->setpPr(toBeErased->getpPr());								// link parent
		}
		else																		// Right child is higher than left child
		{
			ioSs = _minBSTN(rChild);												// in-order successor (ioSs), Right child Node's Min value
			rcIoSs = ioSs->getpRc();
			parIoSs = ioSs->getpPr();
			newSubRoot = ioSs;
			if (ioSs->getpPr() != toBeErased)										// RC ioSs's parent is toBeErased Node
			{
				newSubRoot->setpRc(rChild);											// new subRoot's RC is toBeErased's RC
				parIoSs->setpLc(rcIoSs);
				if (rcIoSs != NULL)													// If RC ioSs's right child isn't NULL
					rcIoSs->setpPr(parIoSs);
			}
			newSubRoot->setpLc(lChild);												// link toBeErased's left child
			newSubRoot->setpPr(toBeErased->getpPr());
		}
		if (lChild != ioPd)
			lChild->setpPr(newSubRoot);												// set newSubRoot
		if (rChild != ioSs)
			rChild->setpPr(newSubRoot);
	}
	if (toBeErased == _root)														// if toBeErased is Root, set new Root
		_root = newSubRoot;
	num_entry--; 
	free(toBeErased);																// erase
	*pptoBeErased = newSubRoot;
	return newSubRoot;
}

template<typename K, typename V>
int T_BST<K, V>::_getHeight(T_BSTN<K, V>* pTN)										// get BST height
{
	int height = 0;
	int height_Lc, height_Rc;
	if (pTN != NULL)
	{
		height_Lc = _getHeight(pTN->getpLc());										// Left child height
		height_Rc = _getHeight(pTN->getpRc());										// Right child height
		if (height_Lc > height_Rc)
			height = 1 + height_Lc;													// child's height + Node
		else
			height = 1 + height_Rc;
	} return height;
}

template<typename K, typename V>
int T_BST<K, V>::_getHeightDiff(T_BSTN<K, V>* pTN)									// defference of left child's height and right child's height
{
	int heightDiff = 0;
	if (pTN == NULL)
		return 0;
	heightDiff = _getHeight(pTN->getpLc()) - _getHeight(pTN->getpRc());				// left height - righrt height
	return heightDiff;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent;
	pCurParent = pCurSubRoot->getpPr();												// Current Node's parent
	pNewSubRoot = pCurSubRoot->getpLc();											// Current Node's LC
	pBR = pNewSubRoot->getpRc();													//				P						P
	pCurSubRoot->setpLc(pBR);														//			A				B
	if (pBR != NULL)																//	B				=>				A
		pBR->setpPr(pCurSubRoot);													//		C						C
	pNewSubRoot->setpRc(pCurSubRoot);												// B's level up
	pNewSubRoot->setpPr(pCurParent);
	pCurSubRoot->setpPr(pNewSubRoot);
	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent;
	pCurParent = pCurSubRoot->getpPr();												// Current Node's parent
	pNewSubRoot = pCurSubRoot->getpRc();											// Current Node's RC
	pBL = pNewSubRoot->getpLc();													//	P						P
	pCurSubRoot->setpRc(pBL);														//		A								B
	if (pBL != NULL)																//				B	=>			A		
		pBL->setpPr(pCurSubRoot);													//			C						C
	pNewSubRoot->setpLc(pCurSubRoot);												// B's level up
	pNewSubRoot->setpPr(pCurParent);
	pCurSubRoot->setpPr(pNewSubRoot);
	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;
	pC = pCurSubRoot;
	pCurParent = pCurSubRoot->getpPr();
	pA = pC->getpLc();														//					C									C
	pB = pA->getpRc();														//	A					rotate_RR				B
	pBL = pB->getpLc();														//			B				=>			A			BR
	pBR = pB->getpRc();														//	   BL        BR							BL
	pSubRoot = _rotate_RR(pA);												// new sub root => B
	pCurSubRoot->setpLc(pSubRoot);

	pNewSubRoot = _rotate_LL(pC);											// 					C							B
	pNewSubRoot->setpPr(pCurParent);										// 			B			rotate_LL		A				C
	pA->setpPr(pNewSubRoot);												// 	A			BR			=>				BL		BR
	pC->setpPr(pNewSubRoot);												// 		BL							

	if (pBL != NULL)
		pBL->setpPr(pA);
	if (pBR != NULL)
		pBR->setpPr(pC);
	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;
	pA = pCurSubRoot;
	pCurParent = pCurSubRoot->getpPr();
	pC = pA->getpRc();														//	A								A
	pB = pC->getpLc();														//					C	rotate_LL			B
	pBL = pB->getpLc();														//			B				=>			BL			C
	pBR = pB->getpRc();														//		BL		BR								BR
	pSubRoot = _rotate_LL(pC);
	pCurSubRoot->setpRc(pSubRoot);
	
	pNewSubRoot = _rotate_RR(pA);											//	A										B
	pNewSubRoot->setpPr(pCurParent);										//			B			rotate_RR	A				C
	pA->setpPr(pNewSubRoot);												//		BL			C		=>			BL		BR
	pC->setpPr(pNewSubRoot);												//				BR					
	if (pBL != NULL)
		pBL->setpPr(pA);
	if (pBR != NULL)
		pBR->setpPr(pC);
	return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)			// BST rebalancing
{
	int heightDiff = 0;
	heightDiff = _getHeightDiff(*ppTN);								// get heighr diff
	if (heightDiff > 1)												// left tree is higher than right tree
	{
		if (_getHeightDiff((*ppTN)->getpLc()) > 0)
			*ppTN = _rotate_LL(*ppTN);
		else
			*ppTN = _rotate_LR(*ppTN);
	}
	else if (heightDiff < -1)										// right tree is higher than left tree
	{
		if (_getHeightDiff((*ppTN)->getpRc()) < 0)
			*ppTN = _rotate_RR(*ppTN);
		else
			*ppTN = _rotate_RL(*ppTN);
	}
	return *ppTN;
}

template<typename K, typename V>
void T_BST<K, V>::insertAndRebalance(T_Entry<K, V> entry)			// insert and rebalance
{
	_insertAndRebalance(&_root, NULL, entry);
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> entry)
{
	T_BSTN<K, V>* pTN, ** ppLc, ** ppRc;
	if (*ppTN == NULL)												// ppTN is root node(if ppTN is NULL, there isn't BST)
	{
		pTN = new T_BSTN<K, V>(entry);								// Dynamic Memory Allocation
		*ppTN = pTN;
		if (pPr != NULL)
			pTN->setpPr(pPr);										// set ROOT's parent Node as NULL
		(*ppTN)->setpLc(NULL);										// set LC, RC as NULL
		(*ppTN)->setpRc(NULL);
		num_entry++;
		return *ppTN;
	}
	T_Entry<K, V> bstn_entry;
	bstn_entry = (*ppTN)->getEntry();
	if (entry < bstn_entry)											// Compare key value, insert value < root value
	{
		ppLc = (*ppTN)->getppLc();
		pTN = _insertAndRebalance(ppLc, *ppTN, entry);
		if (ppTN != NULL)
		{
			(*ppTN)->setpLc(pTN);
			*ppTN = _reBalance(ppTN);
		}
	}
	else															// Compare key value, insert value > root value
	{
		ppRc = (*ppTN)->getppRc();
		pTN = _insertAndRebalance(ppRc, *ppTN, entry);
		if (ppTN != NULL)
		{
			(*ppTN)->setpRc(pTN);
			*ppTN = _reBalance(ppTN);
		}
	}
	return *ppTN;
}

template<typename K, typename V>
void T_BST<K, V>::clear()
{
	delete this->_root;
	this->num_entry = -1;
	this->name = "n";
}

#endif