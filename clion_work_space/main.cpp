#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char me;
	node *next[26];
} node;

node *root;

char source[50010];

void build (int index, node *this_root) {
	if ( index >= strlen(source)) return;
	int i, j, k;
	for ( i = index; i < strlen(source); ++i ) {
		if(!this_root->next[source[i] - 'a']) {
			node *next = ( node * ) malloc(sizeof(node));
			next->me = source[i];
			this_root->next[source[i] - 'a'] = next;
			build(i, next);
		}
	}
}

void output(node *now) {
	int i;
	for ( i = 0; i < 25; ++i ) {
		printf("%c", now->me);
		if(now->next[i]) {
			output(now->next[i]);
		}
	}
}

int main (int argc, char *argv[]) {
//	freopen("circle.in", "r", stdin);
//	freopen("circle.out", "w+", stdout);
	scanf("%s", source);
	root->me = source[0];
	build(0, root);
	return 0;
}

/*
3
1 2 80
2 3 80
3 1 20
 */
