#include "Class_Mtrx.h"
#include <iomanip>
#define SETW 6
typedef double* DBLPTR;				// double pointer를 DBLPTR로 지정

Mtrx::Mtrx(int num_row, int num_col)		// class object constructor
{
	int i, j;
	n_row = num_row; n_col = num_col;
	dM = new DBLPTR[n_row];					// Dynamic memory Allocation
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];			// Dynamic memory Allocation
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			dM[i][j] = 0.0;
		}
	}
}

Mtrx::~Mtrx()					// class object destructor
{
	 /*cout << "destructor of Mtrx ("
	 << name << ")" << endl;
	
	for (int i=0; i<n_row; i++)
	delete [] dM[i];
	delete [] dM;
	*/
}

Mtrx::Mtrx(istream& fin)				// Mtrx data inpit from file
{
	int i, j, size_row, size_col, num_data, cnt;
	double d;
	fin >> size_row >> size_col;
	n_row = size_row;
	n_col = size_col;
	dM = new DBLPTR[n_row];
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			if (fin.eof())				// file 끝에 도달하면 0.0 입력
				dM[i][j] = 0.0;
			else
			{
				fin >> d;
				dM[i][j] = d;
			}
		}
	}
}

void Mtrx::fprintMtrx(ostream& fout)			// printout mtrx
{
	//SETW = 6 6칸에 출력
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	fout << this->name << " = " << endl;
	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < n_col; j++)
		{
			fout.setf(ios::fixed);				// 부동소수점 설정
			fout.precision(1);					// 소수점 1자리
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(SETW) << dM[i][j];
			else if ((i == 0) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a4;
			else if ((i > 0) && (i < (n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(SETW) << dM[i][j];
			else if ((i > 0) && (i < (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a2;
			else if ((i == (n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(SETW) << dM[i][j];
			else if ((i == (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a5;
			else
				fout << setw(SETW) << dM[i][j];
		} fout << endl;
	} fout << endl;
}

Mtrx Mtrx::addMtrx(const Mtrx& mA)			// add Mtrx
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j];
		}
	}
	return mR;
}

Mtrx Mtrx::subMtrx(const Mtrx& mA)			// sub Mtrx
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];
		}
	}
	return mR;
}

Mtrx Mtrx::mulMtrx(const Mtrx& mA)			// mul Mtrx
{
	int i, j, k;
	Mtrx mR(n_row, mA.n_col);
	mR.setName("R");
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < mA.n_col; j++) {
			mR.dM[i][j] = 0.0;
			for (k = 0; k < n_col; k++) {
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];
			}
		}
	}
	return mR;
}
Mtrx Mtrx::transposeMtrx()					// tranpose Mtrx 1,1 2,2 3,3 기준으로 행, 열 swap
{
	int i, j;
	Mtrx mR(n_col, n_row);
	mR.setName("R");
	for (int i = 0; i < n_col ; i++)
	{
		for (int p = 0; p < n_row ; p++)
		{
			mR.dM[i][p] = dM[p][i];
		}
	}
	return mR;
}