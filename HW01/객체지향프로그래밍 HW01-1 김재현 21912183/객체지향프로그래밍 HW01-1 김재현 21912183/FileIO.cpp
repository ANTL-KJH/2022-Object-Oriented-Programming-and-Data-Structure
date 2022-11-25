#include "FileIO.h"

int fileInputData(ifstream& fin, int* data_array, int max_num_data)		// 파일로부터 정수형데이터를 받아 배열에 저장하는 함수
{
	int input_num = 0;
	int count = 0;
	while (!fin.eof())
	{
		fin >> input_num;		// get data from input file
		data_array[count] = input_num;		// 배열에 데이터 입력 
		count++;
	}
	return 0;
}

void getStatistics_fileOut(int* data_array, int num_data, ofstream& fout)		// 데이터를 분석하고 파일에 출력하는 함수
{
	double avg = 0.0, var = 0.0, std_dev = 0.0;
	int sum = 0, max = INT_MIN, min = INT_MAX;
	for (int i = 0; i < num_data; i++)		// find max, min value
	{
		sum += data_array[i];
		if (max < data_array[i])
			max = data_array[i];
		if (min > data_array[i])
			min = data_array[i];
	}
	avg = sum / (double)num_data;			// calculate avg
	for (int i = 0; i < num_data; i++)		// calculate var
	{
		var += pow(data_array[i] - avg, 2);
	}
	var = var / num_data;
	std_dev = sqrt(var);					// calculate std_dev

	fout << "min(" << min << "), max(" << max << "), sum(" << sum << "), avg(" << avg << "), var(" << var << "), std_dev(" << std_dev << ")";		// printout
}