/*
* 프로젝트명 : "객체지향프로그래밍 Lab 12-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - Trie 구조를 이용한 text Processing and Prefix Matching을 test 하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.11.29
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자			일자					Ver				수정내용
* JH KIM					2022.11.29				v1.0			최초 작성
* JH KIM					2022.11.30				v1.01			Trie 구조가 명확하도록 VocaList 수정
* JH KIM					2022.12.01				v1.02			주석문 입력
*/
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "MyVoca.h"
#include "MyVocaList.h"
#include "Trie.h"
#include "TrieNode.h"
using namespace std;

#define MAX_WORD_LENGTH 100
#define NUM_TEST_VOCAS 7

//void test_simple_trie(ostream& fout);
//void test_trie_myVoca(ostream& fout);

int main(void)
{
	ofstream fout;				// output file stream
	fout.open("output.txt");	// output file open
	if (fout.fail())			// file stream check
	{
		cout << "Error in opening output file" << endl; exit;
	}

	Trie<MyVoca*> trie_myVoca("Trie_MyVoca");	// gen Class Trie instance
	TrieNode<MyVoca*>* pTN;						// gen Class TrieNode instance
	MyVoca* pVoca;
	string keyStr;
	char keyWord[MAX_WORD_LENGTH];
	List_pVoca predictVocas;
	List_pVoca_Iter itr;

	// Basic Trie operating test
	MyVoca testVocas[NUM_TEST_VOCAS] =
	{
		MyVoca("xyz", NOUN, { "" }, { "" }),
		MyVoca("ABCD", NOUN, { "" }, { "" }),
		MyVoca("ABC", NOUN, { "" }, { "" }),
		MyVoca("AB", NOUN, { "" }, { "" }),
		MyVoca("A", NOUN, { "" }, { "" }),
		MyVoca("xy", NOUN, { "" }, { "" }),
		MyVoca("x", NOUN, { "" }, { "" })
	};
	fout << "Testing basic operations of trie inserting ..... " << endl;
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
		trie_myVoca.insert(testVocas[i].getKeyWord(), &testVocas[i]);		// insert Voca at Trie
	trie_myVoca.fprintTrie(fout);

	fout << endl << "Testing Trie Destroy..." << endl;
	// End of Basic Trie operating test

	// User Voca Trie operating test
	pVoca = &myToeicVocaList[0];			// User VocaList
	while (pVoca->getKeyWord() != "")
	{
		keyStr = pVoca->getKeyWord();
		trie_myVoca.insert(keyStr, pVoca);	// insert Vocabulary
		pVoca++;
	}
	fout << "Total " << trie_myVoca.size() << " words in trie_myVoca .." << endl;
	trie_myVoca.fprintTrie(fout);			// printout
	while (1)
	{
		cout << endl << "Input any prefix to search in tire (. to finish) : ";
		cin >> keyStr;
		if (keyStr == string("."))			// if input string is ".", break while-loop
			break;
		predictVocas.clear();
		trie_myVoca.findPrefixMatch(keyStr, predictVocas);	// prefix Match
		cout << "list of predictive words with prefix (" << keyStr << "):" << endl;
		itr = predictVocas.begin();
		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr;
			cout << *pVoca << endl;
			++itr;
		}
	}
	cout << endl << "Ereasing trie myVoca . . . " << endl;
	fout << endl << "Ereasing trie myVoca . . . " << endl;
	trie_myVoca.eraseTrie();				// erase Trie
	fout.close();
	return 0;
}
