/*
* ������Ʈ�� : "��ü�������α׷��� Lab 04-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* - Ŭ������ ������ ���������� ���� 2���� ����� ó���ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.09.28
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������		����			����		��������
* JH KIM			2022.09.28			v1.0		���� �ۼ�
*/

#include "Class_Mtrx.h"
#include "MtrxArray.h"

int main()
{
	ifstream fin;
	ofstream fout;
	int n_row, n_col;
	fin.open("Matrix_data.txt");		// ���Ϸκ��� ��� ������ �Է�
	if (fin.fail())						// input file check
	{
		cout << "Error in opening input data file !!" << endl;
		exit;
	}
	fout.open("Result.txt");
	if (fout.fail())					// output file check
	{
		cout << "Error in opening output data file !!" << endl;
		exit;
	}
	MtrxArray mtrx(NUM_MTRX);			// MtrxArray ����

	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];		// 3���� Mtrx�� 0, 1, 2�� �Է�

	mtrx[0].set_name("mtrx[0]");		// setname
	mtrx[1].set_name("mtrx[1]");
	mtrx[2].set_name("mtrx[2]");

	fout << mtrx[0] << endl;			// printout
	fout << mtrx[1] << endl;
	fout << mtrx[2] << endl;

	mtrx[3] = mtrx[0] + mtrx[1];		// add Mtrx
	mtrx[3].set_name("mtrx[3] = mtrx[0] + mtrx[1]"); 
	fout << mtrx[3] << endl;

	mtrx[4] = mtrx[0] - mtrx[1];		// sub Mtrx
	mtrx[4].set_name("mtrx[4] = mtrx[0] - mtrx[1]");
	fout << mtrx[4] << endl;

	mtrx[5] = mtrx[0] * mtrx[2];		// mul Mtrx
	mtrx[5].set_name("mtrx[5] = mtrx[0] * mtrx[2]");
	fout << mtrx[5] << endl;

	mtrx[6] = ~mtrx[5];					// tranpose Mtrx
	mtrx[6].set_name("mtrx[6] = ~mtrx[5] (transposed matrix)");
	fout << mtrx[6] << endl;

	mtrx[7] = mtrx[0];
	mtrx[7].set_name("mtrx[7] = mtrx[0]");
	fout << mtrx[7] << endl;
	if (mtrx[7] == mtrx[0])
		fout << "mtrx[7] and mtrx[0] are equal.\n";
	if (mtrx[5] != mtrx[6])
		fout << "mtrx[5] and mtrx[6] are not equal.\n";
	fin.close();
	fout.close();
	return 0;
}