/*
* ������Ʈ�� : "��ü�������α׷��� HW 01-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* -���Ϸκ��� 10���� ������ �Է¹ް� �м��Ͽ� ����� ����ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.09.02
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������		����			����		��������
* JH KIM			2022.09.02	v1.0	���� �ۼ�
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

    fileInputData(fin, parray, MAX_DATA_NUM);       // input ���Ϸκ��� data�� �������� �Լ�
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

