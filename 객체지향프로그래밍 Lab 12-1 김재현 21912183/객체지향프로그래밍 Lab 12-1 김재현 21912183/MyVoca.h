/*MyVoca.h*/
#ifndef MY_VOCA_H
#define MY_VOCA_H
#include <iostream>
#include <string>
#include <list>

using namespace std;
enum Word_Type { NOUN, VERB, ADJ, ADV, PREPOS };
typedef list<string> List_Str;
typedef list<string>::iterator Lst_Str_Itr;

class MyVoca
{
	friend ostream& operator<<(ostream& fout, MyVoca& mv);
public:
	// Constructor
	MyVoca() { keyWord = ""; }
	MyVoca(string kw, Word_Type wt, List_Str thes, List_Str ex_usg)
		:keyWord(kw), type(wt), thesaurus(thes), usages(ex_usg)
	{ }

	// Accessor
	string getKeyWord() { return keyWord; }

private:
	string keyWord;			// keyWord
	Word_Type type;			// NOUN, VERB, ADJ, ADV, PREPOS
	List_Str thesaurus;		// thesarus of the entry word in the type
	List_Str usages;
};

ostream& operator<<(ostream& fout, MyVoca& mv)								// operator overloading <<
{
	const string wd_ty[] = { "n", "v", "adj", "adv", "prepos" };
	list<string>::iterator itr;
	fout << mv.keyWord << "(" << wd_ty[mv.type] << "): \n";
	fout << " - thesaurus(";
	for (itr = mv.thesaurus.begin(); itr != mv.thesaurus.end(); ++itr)		// printout thesaurus
	{
		fout << *itr << ", ";
	}
	fout << ")" << endl;
	fout << " - example usage(";
	for (itr = mv.usages.begin(); itr != mv.usages.end(); ++itr)			// printout example usage
	{
		fout << *itr << " ";
	}
	fout << ")";
	return fout;
}

#endif