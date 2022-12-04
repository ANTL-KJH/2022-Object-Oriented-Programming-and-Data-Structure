/*genBigRandArray*/
#include "genBigRandArray.h"

int* genBigRandArray(int bigRandArraySize, int offset)		// rand() �Լ��� ������ �ʰ��ϴ� bigrand ���� �����ϴ� �Լ�
{
	int* pBigRandArray;
	int idx1, idx2;
	int temp;
	pBigRandArray = (int*)calloc(bigRandArraySize, sizeof(int));		// Dynamic Memory Allocation
	for (int i = 0; i < bigRandArraySize; i++)				// BigRandArray�� ���� ������Ű�� int�� �Է�
	{
		pBigRandArray[i] = i + offset;
	}
	for (int i = 0; i < bigRandArraySize; i++)
	{
		idx1 = (((long)rand() << 15) | rand()) % bigRandArraySize;
		idx2 = (((long)rand() << 15) | rand()) % bigRandArraySize;
		if (idx1 == idx2) {			// �� �������� ������ continue
			continue;
		}
		else {						// �� �������� �ٸ���� swap
			temp = pBigRandArray[idx1];
			pBigRandArray[idx1] = pBigRandArray[idx2];
			pBigRandArray[idx2] = temp;
		}
	}
	return pBigRandArray;
}
