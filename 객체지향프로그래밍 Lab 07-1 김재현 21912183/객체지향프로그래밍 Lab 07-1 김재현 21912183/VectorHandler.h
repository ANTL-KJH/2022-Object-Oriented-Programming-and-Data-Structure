/*VectorHandler*/
#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H
#include <vector>
#include <algorithm>

template<typename T>
void printVector(vector<T>& v)
{
	string typeName = typeid(T).name();							// Type 이름 입력
	int size = v.size();
	cout << "Vector size(" << v.size() << "), elements : \n";
	typename vector<T>::iterator p;
	for (p = v.begin(); p != v.end(); p++)
	{
		cout << *p << " ";
		if ((typeName == "class Date") || (typeName == "class Time"))			// Type name check
			continue;
		else
			cout << endl;
	}
	/*for (int i = 0; i != v.size(); i++)
	{
		cout << v[i] << " ";
	}*/
	cout << endl;
}
#endif