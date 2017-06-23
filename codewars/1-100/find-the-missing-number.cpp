#include <vector>

#define size 101

using namespace std;

int missingNo(vector<int> arr){
	auto all = new int[size]();
	for (int i = 0; i < size; ++i) all[i] = 0;
	for (int i = 0; i < size - 1; ++i) ++all[arr[i]];
	for (int i = 0; i < size; ++i)
		if (!all[i]) return i;
}

