/*Mystring.cpp*/
#include "MyString.h"
string genRandString(int minLen, int maxLen)				// random string�� ����� �Լ�
{
	string str;
	char* temp_str = (char*)calloc(maxLen+1, sizeof(char));
	int str_len = 0;

	str_len = (rand() % (maxLen - minLen + 1)) + minLen;		// random str_len

	for (int i = 0; i < str_len; i++)
	{
		if (i == 0)
			temp_str[i] = rand() % 26 + 'A';				// ù���ڴ� �빮��
		else
			temp_str[i] = rand() % 26 + 'a';				
					
	}
	temp_str[maxLen] = *"\0";
	str = string(temp_str);									// string ��ȯ
	free(temp_str);
	return str;						// return
}