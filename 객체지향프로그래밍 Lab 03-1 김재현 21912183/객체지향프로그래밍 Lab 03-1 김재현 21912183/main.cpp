/*
* ������Ʈ�� : "��ü�������α׷��� Lab 03-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* - Ŭ������ �̿��Ͽ� 2���� Matrix�� ������ �����ϰ� ����ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.09.23
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������		����			����		��������
* JH KIM			2022.09.23			v1.0		���� �ۼ�
*/
#include "Class_Mtrx.h"			// iostrem �� fstream ���� using namespace std ����
int main()						// main function
{
	ifstream fin;				// file input
	ofstream fout;				// file output
	fin.open("Matrix_data.txt");			// input file open
	if (fin.fail())							// file open�� ������ ���
	{
		cout << "Error in opening Matrix_data.txt !!" << endl; exit;
	}
	fout.open("output.txt");				// output file open
	if (fout.fail())						// file open�� ������ ���
	{
		cout << "Error in opening output.txt !!" << endl; exit;
	}
	Mtrx mtrxA(fin);						// file�� ���� MatrixA�� ������
	mtrxA.setName("mtrxA");					// "mtrxA" setname
	mtrxA.fprintMtrx(fout);					// printout
	Mtrx mtrxB(fin);						// file�� ���� MatrixB�� ������
	mtrxB.setName("mtrxB");					// "mtrxB" setname
	mtrxB.fprintMtrx(fout);					// printout
	Mtrx mtrxC(fin);						// file�� ���� MatrixC�� ������
	mtrxC.setName("mtrxC");					// "mtrxA" setname
	mtrxC.fprintMtrx(fout);					// printout
	Mtrx mtrxD(mtrxA.getN_row(), mtrxB.getN_col());			// MtrxA�� ��� MtrxB�� �� ũ��� MtrxD ����
	mtrxD = mtrxA.addMtrx(mtrxB);							// MtrxA�� MtrxB�� �����Ͽ� MtrxD�� save
	mtrxD.setName("mtrxD = mtrxA.add(mtrxB)");				// MtrxD�� �̸��� mtrxD = mtrxA.add(mtrxB)���� ����
	mtrxD.fprintMtrx(fout);									// printout
	Mtrx mtrxE(mtrxA.getN_row(), mtrxB.getN_col());			// A�� ��� B�� �� ũ��� MtrxE ����
	mtrxE = mtrxA.subMtrx(mtrxB);							// MtrxA���� MtrxB�� ����
	mtrxE.setName("mtrxE = mtrxA.sub(mtrxB)");				// MtrxE�� �̸��� mtrxE = mtrxA.sub(mtrxB)�� ����
	mtrxE.fprintMtrx(fout);									// printout
	Mtrx mtrxF(mtrxA.getN_row(), mtrxC.getN_col());			// A�� �� C�� �� size�� MtrxF ����
	mtrxF = mtrxA.mulMtrx(mtrxC);							// A�� C�� ���� F�� save
	mtrxF.setName("mtrxF = mtrxA.multiply(mtrxC)");
	mtrxF.fprintMtrx(fout);									// printout
	Mtrx mtrxG(mtrxA.getN_col(), mtrxA.getN_row());
	mtrxG = mtrxA.transposeMtrx();
	mtrxG.setName("mtrxG = mtrxA.transposeMtrx()");
	mtrxG.fprintMtrx(fout);									// printout
	fout.close();
	return 0;
}