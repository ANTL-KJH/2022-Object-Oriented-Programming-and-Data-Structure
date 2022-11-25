#include "FileIO.h"

int fileInputData(ifstream& fin, int* data_array, int max_num_data)		// ���Ϸκ��� �����������͸� �޾� �迭�� �����ϴ� �Լ�
{
	int input_num = 0;
	int count = 0;
	while (!fin.eof())
	{
		fin >> input_num;		// get data from input file
		data_array[count] = input_num;		// �迭�� ������ �Է� 
		count++;
	}
	return 0;
}

void getStatistics_fileOut(int* data_array, int num_data, ofstream& fout)		// �����͸� �м��ϰ� ���Ͽ� ����ϴ� �Լ�
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