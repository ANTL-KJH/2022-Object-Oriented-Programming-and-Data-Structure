/* HashDictionary.h */
#ifndef HASHDICT_H
#define HASHDICT_H
#define DEFAULT_HASH_SIZE 100

#include "HashMap.h"

template <typename K, typename V>
class HashDict : public HashMap<K, V>
{
public:
	typedef typename HashMap<K, V>::Iterator Iterator;
	typedef typename HashMap<K, V>::Entry Entry;

	// Range class declaration
	class Range 
	{
	private:
		Iterator _begin;	// front of range
		Iterator _end;		// end of range
	public:
		// constructor and destructor
		Range() {}
		Range(const Iterator& b, const Iterator& e)
			: _begin(b), _end(e) { }

		// mutator and accessor
		Iterator& begin() { return _begin; }	// get beginning
		Iterator& end() { return _end; }		// get end
	};
public:
	// constructor
	HashDict(string name, int capacity = DEFAULT_HASH_SIZE); 

	Range findAll(const K& k);					// find all entries about Key k and return Range of them
	Iterator insert(const K& k, const V& v);	// insert pair (k,v)
};

template <typename K, typename V>				// constructor
HashDict<K, V>::HashDict(string name, int capacity)
	: HashMap<K, V>(name, capacity)
{

}

template <typename K, typename V>				// insert Key and Value
typename HashDict<K, V>::Iterator HashDict<K, V>::insert(const K& k, const V& v)
{
	Iterator p = this->_find(k);				// find key
	Iterator q = this->_insert(p, Entry(k, v)); // insert now position
	return q;
}

template <typename K, typename V>				// find all entries with k
typename HashDict<K, V>::Range HashDict<K, V>::findAll(const K& k)
{
	Iterator b = this->_find(k);
	Iterator p = b;
	while ((p != this->end()) && (*p).getKey() == k)
	{
		++p;
	}
	return Range(b, p);
}
#endif