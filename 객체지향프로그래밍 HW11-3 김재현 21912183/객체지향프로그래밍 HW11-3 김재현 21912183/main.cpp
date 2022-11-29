#include <iostream>
#include <fstream>
#include "GenericSkipList.h"
#include "MyVoca.h"
#include "MyVocaList.h"
#include <string>
using namespace std;
#define NUM_PLANETS 9
void main()
{
	ofstream fout;
	MyVoca* pMyVocaLists;
	pMyVocaLists = new MyVoca[NUM_MY_TOEIC_VOCA];
	fout.open("output.txt");			// open outputfile
	if (fout.fail())
	{
		cout << "output.txt file opening failed !!\n";
		exit(1);
	}
	fout << "Testing SkipList<int, MyVoca*> ..." << endl;
	SkipList<string, MyVoca*> MyVocaSkipList;
	typedef SkipList<string, MyVoca*>::Position Pos_MyVoca;
	Pos_MyVoca pMyVoca;

	string keyWord;
	string deleteList[20] = { "personally", "justly", "forecast", "discontinue", "critical", "customize", "clarity", "promotion", "temporary", "overtime", "marginal", "initiate", "announce", "attractive",
		"argue", "examin", "eventually","rating","financial","launch" };
	fout << " Inserting MyVoca to" << "MyVoca SkipList ..." << endl;

	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		fout << "Inserting MyVoca[";
		fout << i << "]: " << myToeicVocaList[i] << endl;
		keyWord = myToeicVocaList[i].getKeyWord();
		MyVocaSkipList.SkipListInsert(fout, keyWord, &myToeicVocaList[i]);
		MyVocaSkipList.PrintSkipList(fout);
		fout << endl;
	}
	fout << "\nEnd of Testing SkipList" << endl;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		fout << "Search MyVocaSkipList and delete";
		fout << " the MyVoca(";
		fout << deleteList[i] << ") : ";
		//pMyVoca = MyVocaSkipList.SkipListSearch(deleteList[i]);	<<<<=================¿©±â¼­ ÅÍÁü
		if (pMyVoca != Pos_MyVoca(NULL))
		{
			fout << *pMyVoca << endl;
			MyVocaSkipList.SkipListRemove(fout, deleteList[i]);
		}
		MyVocaSkipList.PrintSkipList(fout);
		fout << endl;
	}
}