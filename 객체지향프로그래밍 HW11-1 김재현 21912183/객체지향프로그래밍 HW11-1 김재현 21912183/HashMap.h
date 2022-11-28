/* HashMap.h */
#ifndef HASHMAP_H
#define HASHMAP_H
#include <string>
#include <list>
#include <vector>
#include "cyclicShiftHashCode.h"
#include "Entry.h"
//#include "Exceptions.h"
using namespace std;
int collision = 0;

template <typename K, typename V>
class HashMap
{
public:
	typedef Entry<const K, V> Entry;
	typedef std::list<Entry> Bucket;			// bucket of entries
	typedef std::vector<Bucket> BktArray;		// bucket array
	typedef typename BktArray::iterator BItor;	// Bucket iterator
	typedef typename Bucket::iterator EItor;	// Entry iterator
	class Iterator;
public:
	// constructor
	HashMap(string name, int capacity = 101);

	// accessor
	int size() const { return num_entry; }
	string getName() { return name; }

	bool empty() const { return (num_entry == 0); }		// check Hashmap full
	Iterator find(const K& k);							// find entry with key k
	Iterator insert(const K& k, const V& v);			// insert
	void erase(const K& k);								// remove entry with key k
	void erase(const Iterator& p);						// remove entry at p
	Iterator begin();									// iterator begin point
	Iterator end();										// iterator to end entry
protected:
	Iterator _find(const K& k);							// find value with key
	Iterator _insert(const Iterator& p, const Entry& e);	// insert utility
	void _erase(const Iterator& p);						// remove utility
	static void _next(Iterator& p)						// bucket's next entry
	{
		++p.ent;
	}
	static bool _endOfBkt(const Iterator& p)			// check p is the end pos
	{
		return p.ent == p.bkt->end();
	}
private:
	int num_entry;
	BktArray B;
	string name;
public:
	// Iterator class declaration
	class Iterator
	{
	protected:
		EItor ent;			// entry Iterator
		BItor bkt;			// bucket Iterator
		const BktArray* ba; // which bucket array
	public:
		// constructor
		Iterator() {}
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) { }

		// accessor
		V getValue() { Entry& e = *ent; return e.getValue(); }

		// operator overloading
		bool operator==(const Iterator& p) const;
		bool operator!=(const Iterator& p) const;
		Entry& operator*();				// get entry's address
		Iterator& operator++();			// advance to next entry
		Iterator& advanceEItor()
		{
			++ent;
			return *this;
		}
		friend class HashMap;
	};
};

template <typename K, typename V>		// constructor
HashMap<K, V>::HashMap(string nm, int capacity)
	: num_entry(0), B(capacity)
{

}

template <typename K, typename V>		// return iterator of bucket's front
typename HashMap<K, V>::Iterator HashMap<K, V>::begin()
{
	if (empty())
		return end();					// Data doesn't exist in HashMap
	BItor bkt = B.begin();				// Bucket's begin
	while (bkt->empty())
		++bkt;							// find nonempty bucket
	return Iterator(B, bkt, bkt->begin());	// return first of bucket
}

template <typename K, typename V>		// return iterator of bucket's end
typename HashMap<K, V>::Iterator HashMap<K, V>::end()
{
	return Iterator(B, B.end());
}

template <typename K, typename V>		// return entry
typename HashMap<K, V>::Entry& HashMap<K, V>::Iterator::operator*()
{
	return *ent;
}

template <typename K, typename V>		// Iterator equal check
bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt)		// ba => bucket array
		return false;					// not equal
	else if (bkt == ba->end())
		return true;					// end
	else
		return (ent == p.ent);			// equal check
}

template <typename K, typename V>		// Iterator doesn't equal check
bool HashMap<K, V>::Iterator::operator!=(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt)
		return true;
	else if (bkt == ba->end())
		return false;
	else
		return (ent != p.ent);
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator& HashMap<K, V>::Iterator::operator++()	// operator overloading ++
{
	++ent;
	if (_endOfBkt(*this))
	{
		++bkt;											// go to next bucket
		while (bkt != ba->end() && bkt->empty())		// go to next nonempty bucket
			++bkt;
		if (bkt == ba->end())
			return *this;								// end of bucket array
		ent = bkt->begin();								// first nonempty entry
	} return *this;
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;
	int i = hash(k) % B.size();							// calculate hash value i, using CyclicShiftHashCode(), B size = 64

	BItor bkt = B.begin() + i;
	Iterator p(B, bkt, bkt->begin());					// start of i-th bucket
	while (!_endOfBkt(p) && (*p).getKey() != k)			// linear search for k in the bucket
	{
		++p.ent;
		collision++;									// collision
	}
	return p;
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k);								// find Iterator with key
	if (_endOfBkt(p))									// if p is end, can't find key
		return end();
	else
		return p;
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::_insert(const Iterator& p, const Entry& e)	// insert
{
	EItor ins = p.bkt->insert(p.ent, e);													// insert e at p
	num_entry++;
	cout << "B:size" << B.size();
	return Iterator(B, p.bkt, ins);															// return this position
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k);								// search key
	if (_endOfBkt(p))									// if p is end, can't find key
	{
		return _insert(p, Entry(k, v));					// insert at end of bucket
	}
	else
	{
		p.ent->setValue(v);								// replace value
		return p;
	}
}

template <typename K, typename V>
void HashMap<K, V>::_erase(const Iterator& p)			// erase, remove with Iterator
{
	p.bkt->erase(p.ent);								// remove entry from bucket
	num_entry--;
}

template <typename K, typename V>
void HashMap<K, V>::erase(const Iterator& p)			// erase, remove
{
	_erase(p);
}

template <typename K, typename V>
void HashMap<K, V>::erase(const K& k)					// erase, remove with key
{
	Iterator p = _find(k);								// find k
	//if (_endOfBkt(p)) // not found?
	//	throw NonexistentElement("Erase of nonexistent"); // ...error
	_erase(p);											// remove
}
#endif