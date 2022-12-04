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

// ASCII CODE A~Z(65~90), a~z(97~122)
// "mean" => CyclicShiftHashCode 
// 
// Cycle 0
// h = 0 
// h + "m" = 109 => binary => 0110 1101
// 
// Cycle 1
// shift left 5bits, h = 1101 1010 0000
// shift right 27bits, h = 0000 0000 0000
// or, h = 1101 1010 0000
// h + "e" = 1110 0000 0101
// 
// Cycle 2
// shift left 5bits, h = 0001 1100 0000 1010 0000
// shift right 27bits, h = 0000 0000 0000
// or, h = 0001 1100 0000 1010 0000
// h + "a" = 0001 1100 0001 0000 0001
// 
// Cycle 3
// shift left 5bits, h = 0011 1000 0010 0000 0010 0000
// shift right 27bits, h = 0000 0000 0000
// or, h = 0011 1000 0010 0000 0010 0000
// h + "n" = 0011 1000 0010 0000 1000 1110
//
// return h = 0011 1000 0010 0000 1000 1110
//

#endif