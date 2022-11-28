/* cyclicShiftHashCode.h */
#ifndef CYCLIC_SHIFT_HASHCODE_H
#define	CYCLIC_SHIFT_HASHCODE_H

#include <string>
using namespace std;

#define BIT_SHIFTS 5												// Shift 5bits
#define BITS_INT 32													// use 32 bits

class CyclicShiftHashCode
{
public:
	int operator() (const string key)								// CyclicShiftHashCode
	{
		int len = key.length();
		unsigned int h = 0;
		for (int i = 0; i < len; i++)
		{
			h = (h << BIT_SHIFTS) | (h >> (BITS_INT - BIT_SHIFTS));	// (shift left 5bits) or (shift right 27 bits)
			h += (unsigned int)key.at(i);
		}
		return h;
	}
};

#endif