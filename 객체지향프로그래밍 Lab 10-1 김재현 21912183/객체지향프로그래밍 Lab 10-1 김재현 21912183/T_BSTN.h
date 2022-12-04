/*T_BSTN.h*/
#ifndef T_BSTN_H
#define T_BSTN_H

#include "T_Entry.h"

template<typename K, typename V>
class T_BSTN
{
public:
	// Constructor
	T_BSTN() : entry(), pPr(NULL), pLc(NULL), pRc(NULL) { }
	T_BSTN(T_Entry<K, V> e) : entry(e), pPr(NULL), pLc(NULL), pRc(NULL) { }
	
	// Accessor
	K getKey() { return entry.getKey(); }
	V getValue() { return entry.getValue(); }
	T_Entry<K, V>& getEntry() { return entry; }
	T_BSTN<K, V>* getpPr() { return pPr; }
	T_BSTN<K, V>* getpLc() { return pLc; }
	T_BSTN<K, V>* getpRc() { return pRc; }
	T_BSTN<K, V>** getppLc() { return &pLc; }
	T_BSTN<K, V>** getppRc() { return &pRc; }
	
	// Mutator
	void setEntry(T_Entry<K, V> e) { entry = e; }
	void setpPr(T_BSTN<K, V>* pTN) { pPr = pTN; }
	void setpLc(T_BSTN<K, V>* pTN) { pLc = pTN; }
	void setpRc(T_BSTN<K, V>* pTN) { pRc = pTN; }

	// operator overloading
	T_Entry<K, V>& operator*() { return entry; }
private:
	T_Entry<K, V> entry;		// element value
	T_BSTN<K, V>* pPr;			// parent
	T_BSTN<K, V>* pLc;			// left child
	T_BSTN<K, V>* pRc;			// right child
};

#endif