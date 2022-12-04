/*
* 프로젝트명 : "객체지향프로그래밍 Lab 10-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - 클래스와 템플릿을 이용하여 BST를 구현하고 Book data를 처리하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.11.13
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자			일자					버전			수정내용
* JH KIM				2022.11.13			v1.0		최초 작성
* JH KIM				2022.11.14			v1.1		T_Array.h 작성
* JH KIM				2022.11.16			v1.2		BST.h clear func 작성
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>		// for stringstream
#include "T_BSTN.h"
#include "T_Entry.h"
#include "T_BST.h"
#include "T_Array.h"
#include "Book.h"
#include "Date.h"
using namespace std;

Book* fGetBookRecords(string fin_name, int* pNum_books)					// get book records from file
{
	int num_books, isbn, yr, mn, dy;
	string bk_title, author_name, date_str;
	Date pd;
	ifstream fin(fin_name);					// input file stream
	fin >> num_books;						// get number of books
	Book* books = new Book[num_books];		// dynamic memory allocation
	*pNum_books = num_books;
	cout << "Number of books (from file) = " << num_books << endl;
	for (int i = 0; i < num_books; i++)
	{
		fin >> bk_title >> author_name >> date_str >> isbn;				// input data from file
		for (int i = 0; i < date_str.size(); i++)
		{
			if (date_str[i] == '-')										// convert date form (2022-11-16 => 2022 11 16)
				date_str[i] = ' ';
		}
		stringstream date_strstream;
		date_strstream.str(date_str);
		date_strstream >> yr >> mn >> dy;								// get yr, mn, dy
		cout << "input book_record (" << bk_title;
		cout << ", " << author_name;
		cout << ", (" << yr << ", " << mn << ", " << dy;
		cout << "), " << isbn << ")" << endl;
		books[i] = Book(bk_title, author_name, Date(yr, mn, dy), isbn);	// input class object
	}
	fin.close();
	return books;
}


int main(void)
{
	Book* books;
	int num_books;
	books = fGetBookRecords("books.txt", &num_books);					// get book records from txt file
	ofstream fout("output.txt");										// output file open
	if (fout.fail())													// output file check
	{
		cout << "Fail to create output.txt for results !!" << endl;
		exit(1);
	}

	fout << "Input books[] array : " << endl;
	for (int i = 0; i < num_books; i++)									// printout book data
	{
		fout << books[i] << endl;
	}
	fout << endl;
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-title" << endl;

	T_Entry<string, Book*> entry_title_pBK;								// generate Template object
	T_BST<string, Book*> BBST_BK_keyTitle("BBST_BK_keyTitle");
	T_BSTN<string, Book*>* pRoot, ** ppBBST_BK_root;
	ppBBST_BK_root = BBST_BK_keyTitle.getRootAddr();					// get root address
	
	for (int i = 0; i < num_books; i++)
	{
		entry_title_pBK.setKey(books[i].getTitle());					// Set Key
		entry_title_pBK.setValue(&books[i]);							// Set Value
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;

		BBST_BK_keyTitle.insertAndRebalance(entry_title_pBK);			// insert data and rebalancing
	}
	fout << "\nEntries in " << BBST_BK_keyTitle.getName() << " (in order of Book Title) : " << endl;		// print out
	//BBST_BK_keyTitle.fprint_inOrder(fout);
	BBST_BK_keyTitle.fprint_with_Depth(fout);
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;

	T_Entry<string, Book*> entry_Author_pBK;							// generate Template object
	T_BST<string, Book*> BBST_BK_keyAuthor("BBST_BK_keyAuthor");
	T_BSTN<string, Book*>** ppRoot_BBST_BK_keyAuthor, * pBBST_BK_keyAuthor;
	ppRoot_BBST_BK_keyAuthor = BBST_BK_keyAuthor.getRootAddr();			// get root address

	for (int i = 0; i < num_books; i++)
	{
		entry_Author_pBK.setKey(books[i].getAuthor());					// Set Key
		entry_Author_pBK.setValue(&books[i]);							// Set Value
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyAuthor.insertAndRebalance(entry_Author_pBK);			// insert data and rebalancing
	}
	fout << "\nEntries in " << BBST_BK_keyAuthor.getName() << " (in order of Book Author) : " << endl;
	//BBST_BK_keyAuthor.fprint_inOrder(fout);
	BBST_BK_keyAuthor.fprint_with_Depth(fout);
	
	// Testing Search on Binary Search Tree
	string author = books[0].getAuthor();								// author Key
	Date d1, d2;														// Date Key
	Book* pBk;
	T_Array<Book*> array_pBook(1, string("Array_Book"));
	d1.setDate(2010, 1, 1);
	d2.setDate(2015, 12, 31);
	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(author);
	BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, array_pBook);
	fout << "Books of author (" << author << ") published during " << d1 << " ~ " << d2 << ":" << endl;
	for (int i = 0; i < array_pBook.size(); i++)
	{
		if (array_pBook[i]->getAuthor() == author)
		{
			pBk = array_pBook[i];
			if ((pBk->getPubDate() >= d1) && (pBk->getPubDate() <= d2))
				fout << *(array_pBook[i]) << endl;
		}
	}
	fout << endl << "Balanced Binary Search Tree (BBST) with key publication-date" << endl;


	T_Entry<Date, Book*> entry_PubDate_pBK;								// generate Template object
	T_BST<Date, Book*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
	T_BSTN<Date, Book*>** ppRoot_BBST_BK_keyPubDate;
	ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.getRootAddr();		// get root address

	for (int i = 0; i < num_books; i++)
	{
		entry_PubDate_pBK.setKey(books[i].getPubDate());					// Set Key
		entry_PubDate_pBK.setValue(&books[i]);								// Set Value
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyPubDate.insertAndRebalance(entry_PubDate_pBK);			// insert data and rebalancing
	}
	fout << "\nEntries in " << BBST_BK_keyPubDate.getName() << " (in order of Book Publication Date) : " << endl;
	BBST_BK_keyPubDate.fprint_inOrder(fout);
	BBST_BK_keyPubDate.fprint_with_Depth(fout);
	fout << "\nRemoving the root entry in sequence ..." << endl;

	for (int i = 0; i < num_books; i++)
	{
		pRoot = BBST_BK_keyTitle.getRoot();
		entry_title_pBK = pRoot->getEntry();
		fout << "\nremove " << entry_title_pBK << endl;
		BBST_BK_keyTitle.eraseBSTN(&pRoot);									// dynamic memory free 
		BBST_BK_keyTitle.fprint_with_Depth(fout);
	}
	fout << "\nClearing BBST_BKs . . . " << endl;
	BBST_BK_keyTitle.clear();
	BBST_BK_keyAuthor.clear();
	BBST_BK_keyPubDate.clear();
	fout << "All BBST_BKs cleared !! " << endl;
	fout.close();
	if (books != NULL)
		delete[] books;

	return 0;
}