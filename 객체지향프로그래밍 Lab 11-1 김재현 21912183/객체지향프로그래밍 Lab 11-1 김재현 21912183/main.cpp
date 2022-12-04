/*
* ������Ʈ�� : "��ü�������α׷��� Lab 11-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* - 
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.11.22
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������			����					����			��������
* JH KIM				2022.11.22			v1.0		���� �ۼ�
* JH KIM				2022.11.23			v1.1		Entry.h ���� 
*/
#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.h"
#include "CyclicShiftHashCode.h"
#include "Entry.h"
#include "HashDictionary.h"
#include "MyVoca.h"
#include "MyVocaList.h"
using namespace std;

int main()
{
	// variable declaration
	ofstream fout;											
	MyVoca* pVoca, voca;
	List_Str thesaurus, usages;
	int word_count;
	MyVoca mv;
	string keyWord;

	// class instance declaration
	HashDict<string, MyVoca*> myVocaDict("MyVocaDict");
	HashDict<string, MyVoca*>::Iterator itr;
	HashDict<string, MyVoca*>::Range range;
	Entry<string, MyVoca*> vocaEntry;

	fout.open("output.txt");								// output txt file open
	if (fout.fail())										// output file stream check
	{
		cout << "Fail to open output.txt !!" << endl;
		exit(1);
	}
	fout << "Inserting My Vocabularies to " << myVocaDict.getName() << " . . . " << endl;

	word_count = 0;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		pVoca = &myToeicVocaList[i];						// Voca list
		keyWord = myToeicVocaList[i].getKeyWord();			// get keyword
		myVocaDict.insert(keyWord, pVoca);					// insert voca
	}
	//cout << endl;
	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .." << endl;
	// check all vocabularies in the hash_dictionary

	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.getValue();								// get Value
		fout << *pVoca << endl;								// printout
	}
	fout << endl;

	//string testWord = "mean";								// test word => "mean"
	string testWord = "offer";								// test word => "offer"
	range = myVocaDict.findAll(testWord);					// find testword, return range
	fout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.getValue();								// get Value
		fout << *pVoca << endl;
	}
	fout << endl;
	fout.close();
	return 0;
}