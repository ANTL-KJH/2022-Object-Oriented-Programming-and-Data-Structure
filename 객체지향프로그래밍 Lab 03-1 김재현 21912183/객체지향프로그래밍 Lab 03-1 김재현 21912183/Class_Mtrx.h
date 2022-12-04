#ifndef MTRX_H
#define MTRX_H
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_SIZE 100
class Mtrx {
public:
	Mtrx(int num_row, int num_col);
	Mtrx(istream& fin);
	~Mtrx(); // destructor
	int getN_row() { return n_row; }
	int getN_col() { return n_col; }
	void setName(string nm) { name = nm; };
	string getName() { return name; };
	Mtrx addMtrx(const Mtrx&);
	Mtrx subMtrx(const Mtrx&);
	Mtrx mulMtrx(const Mtrx&);
	Mtrx transposeMtrx();
	void fprintMtrx(ostream& fout);
private:
	string name;
	int n_row;
	int n_col;
	double** dM;
};
#endif