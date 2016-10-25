#include <stdio.h>
#include <string.h>

#define false 0
#define true 1

const int size = 10000 + 1;

typedef struct pair {
	int left;
	int right;
} pair ;


int main(int argc,char* argv[]) {
	pair aaa;
	pair *a = &aaa;
	a->left = -1;
	a->right = -1;
	int i, j;
	int N;
	int left = size;
	int right = 0;
	int k[size];
	
	memset(k, 0, sizeof(k));

	scanf("%d", &N);

	for(i = 0; i < N; i++) {
		scanf("%i %i", &a->left, &a->right);

		if(a->left < left)
			left = a->left;

		if(a->right > right)
			right = a->right;

		for(j = a->left; j < a->right; j++)
			k[j] = true;
	}

	for(i = left; i < right; i++)
		if(!k[i]) {
			printf("no");
			return 0;
		}

	printf("%i %i", left, right);
	return 0;
}

/*
5
5 6
1 5
10 10
6 9
8 10
*/

