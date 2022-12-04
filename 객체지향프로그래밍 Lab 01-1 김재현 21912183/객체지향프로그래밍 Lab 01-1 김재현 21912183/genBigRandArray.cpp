/*genBigRandArray*/
#include "genBigRandArray.h"

int* genBigRandArray(int bigRandArraySize, int offset)		// rand() 함수의 범위를 초과하는 bigrand 값을 생성하는 함수
{
	int* pBigRandArray;
	int idx1, idx2;
	int temp;
	pBigRandArray = (int*)calloc(bigRandArraySize, sizeof(int));		// Dynamic Memory Allocation
	for (int i = 0; i < bigRandArraySize; i++)				// BigRandArray에 값을 증가시키며 int값 입력
	{
		pBigRandArray[i] = i + offset;
	}
	for (int i = 0; i < bigRandArraySize; i++)
	{
		idx1 = (((long)rand() << 15) | rand()) % bigRandArraySize;
		idx2 = (((long)rand() << 15) | rand()) % bigRandArraySize;
		if (idx1 == idx2) {			// 두 랜덤값이 같으면 continue
			continue;
		}
		else {						// 두 랜덤값이 다른경우 swap
			temp = pBigRandArray[idx1];
			pBigRandArray[idx1] = pBigRandArray[idx2];
			pBigRandArray[idx2] = temp;
		}
	}
	return pBigRandArray;
}
