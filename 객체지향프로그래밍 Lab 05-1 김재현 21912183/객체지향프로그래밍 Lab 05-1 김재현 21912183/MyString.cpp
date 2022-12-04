/*Mystring.cpp*/
#include "MyString.h"
string genRandString(int minLen, int maxLen)				// random string을 만드는 함수
{
	string str;
	char* temp_str = (char*)calloc(maxLen+1, sizeof(char));
	int str_len = 0;

	str_len = (rand() % (maxLen - minLen + 1)) + minLen;		// random str_len

	for (int i = 0; i < str_len; i++)
	{
		if (i == 0)
			temp_str[i] = rand() % 26 + 'A';				// 첫글자는 대문자
		else
			temp_str[i] = rand() % 26 + 'a';				
					
	}
	temp_str[maxLen] = *"\0";
	str = string(temp_str);									// string 변환
	free(temp_str);
	return str;						// return
}