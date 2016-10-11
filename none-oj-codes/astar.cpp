#include <stdio.h>

typedef struct node {
	// location x
	int x;
	// location y
	int y;
	int t;
	// parent
	node *p;
} node ;

int isBlocked(char a) {
	// TODO: check if it's blocked
	return 0;
}

int main(int argc, char *argv[]) {
	int i, j, size, oli = 0;
	node s, e;
	node ol[1000];
	char a[1000][1000];
	scanf("%d", &size);
	for(i = 0; i < size; i++)
		scanf("%s", a[i]);
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			if(isBlocked(a[i][j])) {
				//
			}
			if(isStart(a[i][j])) {
				s.x = i;
				s.y = j;
			}
			if(isEnd(a[i][j])) {
				e.x = i;
				e.y = j;
			}
		}
	}
	ol[oli++] = s;
	do {
		//
	} while();
	return 0;
}
