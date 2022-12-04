/*
* 프로젝트명 : "객체지향프로그래밍 Lab 03-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - 클래스를 이용하여 2차원 Matrix의 연산을 수행하고 출력하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.09.23
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자		일자			버전		수정내용
* JH KIM			2022.09.23			v1.0		최초 작성
*/
#include "Class_Mtrx.h"			// iostrem 및 fstream 포함 using namespace std 포함
int main()						// main function
{
	ifstream fin;				// file input
	ofstream fout;				// file output
	fin.open("Matrix_data.txt");			// input file open
	if (fin.fail())							// file open이 실패한 경우
	{
		cout << "Error in opening Matrix_data.txt !!" << endl; exit;
	}
	fout.open("output.txt");				// output file open
	if (fout.fail())						// file open이 실패한 경우
	{
		cout << "Error in opening output.txt !!" << endl; exit;
	}
	Mtrx mtrxA(fin);						// file로 부터 MatrixA를 가져옴
	mtrxA.setName("mtrxA");					// "mtrxA" setname
	mtrxA.fprintMtrx(fout);					// printout
	Mtrx mtrxB(fin);						// file로 부터 MatrixB를 가져옴
	mtrxB.setName("mtrxB");					// "mtrxB" setname
	mtrxB.fprintMtrx(fout);					// printout
	Mtrx mtrxC(fin);						// file로 부터 MatrixC를 가져옴
	mtrxC.setName("mtrxC");					// "mtrxA" setname
	mtrxC.fprintMtrx(fout);					// printout
	Mtrx mtrxD(mtrxA.getN_row(), mtrxB.getN_col());			// MtrxA의 행과 MtrxB의 열 크기로 MtrxD 생성
	mtrxD = mtrxA.addMtrx(mtrxB);							// MtrxA와 MtrxB를 덧셈하여 MtrxD에 save
	mtrxD.setName("mtrxD = mtrxA.add(mtrxB)");				// MtrxD의 이름을 mtrxD = mtrxA.add(mtrxB)으로 설정
	mtrxD.fprintMtrx(fout);									// printout
	Mtrx mtrxE(mtrxA.getN_row(), mtrxB.getN_col());			// A의 행과 B의 열 크기로 MtrxE 생성
	mtrxE = mtrxA.subMtrx(mtrxB);							// MtrxA에서 MtrxB를 뺄셈
	mtrxE.setName("mtrxE = mtrxA.sub(mtrxB)");				// MtrxE의 이름을 mtrxE = mtrxA.sub(mtrxB)로 설정
	mtrxE.fprintMtrx(fout);									// printout
	Mtrx mtrxF(mtrxA.getN_row(), mtrxC.getN_col());			// A의 행 C의 열 size로 MtrxF 생성
	mtrxF = mtrxA.mulMtrx(mtrxC);							// A와 C의 곱을 F에 save
	mtrxF.setName("mtrxF = mtrxA.multiply(mtrxC)");
	mtrxF.fprintMtrx(fout);									// printout
	Mtrx mtrxG(mtrxA.getN_col(), mtrxA.getN_row());
	mtrxG = mtrxA.transposeMtrx();
	mtrxG.setName("mtrxG = mtrxA.transposeMtrx()");
	mtrxG.fprintMtrx(fout);									// printout
	fout.close();
	return 0;
}