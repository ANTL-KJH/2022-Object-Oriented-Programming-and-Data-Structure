#ifndef FileIO_H
#define FileIO_H
#include <iostream>	// input output stream
#include <fstream>	// file stream
#include <limits.h>
#include <math.h>
#define MAX_DATA_NUM 10
using namespace std;

int fileInputData(ifstream& fin, int* data_array, int max_num_data);
void getStatistics_fileOut(int* data_array, int num_data, ofstream& fout);
#endif