/*Book.h*/
#ifndef CLASS_BOOK
#define CLASS_BOOK

#include "Date.h"

class Book
{
	friend ostream& operator<<(ostream& fout, Book& bk)
	{
		fout.setf(ios::left);
		fout << "[" << setw(8) << bk.title << ", " << setw(8) << bk.author << ", " << bk.pubDate;
		fout << ","  << bk.isbn << "]";
		return fout;
	}
public:
	Book() {}																// default constructor
	Book(string bk_title, string bk_author, Date pd, int bn) 				// constructor
		:title(bk_title), author(bk_author), pubDate(pd), isbn(bn) {}

	// mutator of class book
	string& getTitle() { return title; }
	string getAuthor() { return author; }
	Date getPubDate() { return pubDate; }
	int getISBN() { return isbn; }

	// accessor of class book
	void setTitle(string bk_title) { title = bk_title; }
	void setAuthor(string bk_author) { author = bk_author; }
	void setPubDate(Date pd) { pubDate = pd; }
	void setISBN(int bn) { isbn = bn; }
private:
	string title;
	string author;
	Date pubDate;															// date of publish
	int isbn;																// international standard book number
};
#endif