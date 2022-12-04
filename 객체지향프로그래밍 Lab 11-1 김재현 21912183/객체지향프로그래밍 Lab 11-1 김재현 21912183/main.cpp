/*
* 프로젝트명 : "객체지향프로그래밍 Lab 11-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - 
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.11.22
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자			일자					버전			수정내용
* JH KIM				2022.11.22			v1.0		최초 작성
* JH KIM				2022.11.23			v1.1		Entry.h 수정 
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