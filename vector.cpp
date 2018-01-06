// vector.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vector.h"
#include <istream>
using namespace std;
int main()
{
//	vector<int>vec;
//	cout << vec.begin() << " " << vec.end() << endl;
//	vector<int>vec1(2,3);
//	int array[] = { 1,2,3 };
	vector<int>vec(2, 4);
//	vector<int>vec1(vec);
	vec.push_back(6);								//4 6 6
	vec.insert(vec.begin() + 1, 3, 1);				//4 1 1 1 4 6
	vec.resize(8, 3);								//4 1 1 1 4 6 3 3
	vec.erase(vec.begin() + 2, vec.begin() + 4);	//4 1 4 6 3 3

	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << " ";
//	vec.push_back(1);
    return 0;
}

