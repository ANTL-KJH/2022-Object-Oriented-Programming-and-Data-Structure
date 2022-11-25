/*
* 프로젝트명 : "객체지향프로그래밍 HW 01-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* -파일로부터 10개의 정수를 입력받고 분석하여 결과를 출력하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.09.02
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자		일자			버전		수정내용
* JH KIM			2022.09.02	v1.0	최초 작성
*/

#include <iomanip>
#include "FileIO.h"


int main(void)
{
    ifstream fin;
    ofstream fout;
    int* parray;
    parray = (int*)calloc(10, sizeof(int));     // Dynamic Memory Allocation
    fin.open("input.txt");      // input file open
    fout.open("output.txt");    // output file open
    if (fin.fail())             // input file open error
    {
        cout << "Fail to open an input file (input.txt)" << endl;
    }
    if (fout.fail())            //output file open error
    {
        cout << "Fail to open an input file (input.txt)" << endl;
    }

    fileInputData(fin, parray, MAX_DATA_NUM);       // input 파일로부터 data를 가져오는 함수
    fout << "Total" << MAX_DATA_NUM << "input from inpu data file." << endl;
    fout << "Total" << MAX_DATA_NUM << "integer data : {";
    for (int i = 0; i < MAX_DATA_NUM; i++)          // printout
    {
        fout << parray[i] << ", ";
    }
    fout << "}" << endl;
    getStatistics_fileOut(parray, MAX_DATA_NUM, fout);      // analyse data and printout
    fin.close();    fout.close();   free(parray);           // file close and memory free
    return 0;
}

