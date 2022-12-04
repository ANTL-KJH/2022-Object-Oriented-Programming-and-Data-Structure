#include "Class_Mtrx.h"
typedef double* DBLPTR;

Mtrx::Mtrx()								// constructor
{

}

Mtrx::Mtrx(string nm, int num_row, int num_col)		// class object constructor
{
	int i, j;
	name = nm;
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

Mtrx::Mtrx(string nm, double** pA, int row, int col)
{
	name = nm;
	n_row = row;
	n_col = col;
	for (int i = 0; i < row; i++)
	{
		for (int q = 0; q < col; q++)
		{
			dM[i][q] = pA[i][q];
		}
	}
}

Mtrx::Mtrx(istream& fin)				// Mtrx data inpit from file
{
	int i, j, size_row, size_col, num_data, cnt;
	double d;

	fin >> size_row >> size_col;
	n_row = size_row;
	n_col = size_col;

	dM = new DBLPTR[n_row];				// Dynamic Memory Allocation
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];		// Dynamic Memory Allocation
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

Mtrx::~Mtrx()					// class object destructor
{
	/*cout << "destructor of Mtrx ("
	<< name << ")" << endl;

   for (int i=0; i<n_row; i++)
   delete [] dM[i];
   delete [] dM;
   */
}


istream& operator>> (istream& fin, Mtrx& m)			// >>연산자 오버로딩 => Mtrx Input
{
	int i, j, num_row, num_col, cnt;
	double d;
	fin >> num_row >> num_col;						// file에서 행렬 size input
	m.n_row = num_row;
	m.n_col = num_col;
	m.dM = new DBLPTR[m.n_row];						// Dynamic Memory Allocation
	for (i = 0; i < m.n_row; i++)
	{
		m.dM[i] = new double[m.n_col];
	}
	cnt = 0;
	for (i = 0; i < m.n_row; i++) {
		for (j = 0; j < m.n_col; j++) {
			if (!fin.eof())
			{
				fin >> d;
				m.dM[i][j] = d;
				cnt++;
			}
			else
			{
				m.dM[i][j] = 0.0;
			}
		}
	}
	return fin;
}

ostream& operator<<(ostream& fout, const Mtrx& m)			// <<연산자 오버로딩 => Mtrx Output
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	fout << m.name << endl;
	int n_row, n_col;
	n_row = m.get_n_row();
	n_col = m.get_n_col();
	for (int i = 0; i < n_row; i++) {						// Mtrx 출력
		for (int j = 0; j < n_col; j++)
		{
			fout.setf(ios::fixed);							// 부동 소수점 표시
			fout.precision(2);								// 소수점 2자리
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(SETW) << m.dM[i][j];
			else if ((i == 0) && (j == (n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a4;
			else if ((i > 0) && (i < (n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(SETW) << m.dM[i][j];
			else if ((i > 0) && (i < (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a2;
			else if ((i == (n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(SETW) << m.dM[i][j];
			else if ((i == (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << m.dM[i][j] << a6 << a5;
			else
				fout << setw(SETW) << m.dM[i][j];
		} fout << endl;
	} fout << endl;
	return fout;
}

const Mtrx Mtrx::operator+(const Mtrx& mA)					// Mtrx add
{
	int i, j;
	Mtrx mR("mR", n_row, n_col);							// 임시 Mtrx mR 생성
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j];
		}
	}
	return mR;
}

const Mtrx Mtrx::operator-(const Mtrx& mA)					// Mtrx sub
{
	int i, j;
	Mtrx mR("mR", n_row, n_col);							// 임시 Mtrx mR 생성					
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];
		}
	}
	return mR;
}

const Mtrx Mtrx::operator* (const Mtrx& mA)					// Mtrx mul
{
	int i, j, k;
	Mtrx mR("mR", n_row, mA.n_col);							// 임시 Mtrx mR 생성
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

const Mtrx Mtrx::operator~()								// Mtrx transpose
{
	int i, j;
	Mtrx mR("mR", n_col, n_row);							// 임시 Mtrx mR 생성
	for (i = 0; i < n_row; i++) {
		for (j = 0; j < n_col; j++) {
			mR.dM[j][i] = dM[i][j];
		}
	}
	return mR;
}

bool Mtrx::operator==(const Mtrx& mA)				// 두 개의 Mtrx가 같으면 True 반환
{
	for (int i = 0; i < n_row; i++)
	{
		for (int q = 0; q < n_col; q++)
		{
			if (dM[i][q] != mA.dM[i][q])			// Mtrx의 원소가 하나라도 다르면 False return
				return FALSE;
		}
	}
	return TRUE;
}

bool Mtrx::operator!=(const Mtrx& mA)				// 두 개의 Mtrx가 다르면 True 반환
{
	for (int i = 0; i < n_row; i++)
	{
		for (int q = 0; q < n_col; q++)
		{
			if (dM[i][q] != mA.dM[i][q])			// Mtrx의 원소가 하나라도 다르면 True return
				return TRUE;
		}
	}
	return FALSE;
}

const Mtrx& Mtrx::operator=(const Mtrx& mA)			// Mtrx를 대입하는 함수
{

	this->name = mA.name;
	this->n_row = mA.n_row;
	this->n_col = mA.n_col;
	this->dM = new DBLPTR[n_row];
	for (int i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];		// Dynamic Memory Allocation
	}
	for (int i = 0; i < n_row; i++)
	{
		for (int q = 0; q < n_col; q++)
		{
			this->dM[i][q] = mA.dM[i][q];
		}
	}
	return *this;
}