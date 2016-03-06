//
// Created by asus1 on 2016/3/5.
//

#include<iostream>
using namespace std;
const int size = 5;

int mai3n(int argc, char** argv) {
	int a[size][size],count = 1;
	int k = 0,n = size;
	while( k < n ) {
		//first calculate the outermost number
		for (int i = k; i < n; i++)
			a[k][i] = count++;
		for (int i = k + 1; i < n; i++)
			a[i][n-1] = count++;
		for(int i = n - 2; i >= k; i--)
			a[n-1][i] = count++;
		for(int i = n - 2; i > k; i--)
			a[i][k] = count++;
		n--,k++;
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cout << a[i][j] << "\t" ;
		cout << endl;
	}
//	system("pause");
	return 0;
}
