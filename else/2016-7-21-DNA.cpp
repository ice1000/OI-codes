#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
using namespace std;

typedef struct {
	int step;
	int origin;
	int target;
} node ;

char origin[5001];
char target[5001];
int c[3], fucker, finally_done_step;
bool done = false;

bool judge(node no) {
	if (no.target >= strlen(target)) {
		done = true;
		finally_done_step = no.step;
	}
	return done;
}

bool revert(node n) {
	return origin[n.origin] == 'C' && target[n.target] == 'G' ||
		   origin[n.origin] == 'G' && target[n.target] == 'C' ||
		   origin[n.origin] == 'T' && target[n.target] == 'A' ||
		   origin[n.origin] == 'A' && target[n.target] == 'T' ;
}

int main(int argc, char* argv[]) {
	freopen("DNA.in", "r", stdin);
	freopen("DNA.out","w+",stdout);
	queue<node> q;
	int i, j;
	while(!q.empty()) q.pop();
	scanf("%i%i%i", &c[0], &c[1], &c[2]);
	scanf("%s%s", origin, target);
	node n;
	n.step = 0;
	n.origin = 0;
	n.target = 0;
	q.push(n);
	while(!q.empty() && !done) {
		n = q.front();
		q.pop();
		// delete origin
		n.target++;
		n.step += c[2];
		if (judge(n)) break;
		q.push(n);
		// reverse
		n.step -= c[2];
		n.target--;
		// origin still available
		if (n.origin < strlen(origin)) {
			// add to target
			n.origin++;
			n.step += c[1];
			q.push(n);
			// reverse
			n.origin--;
			n.step -= c[1];
			// add to target from origin
			if(origin[n.origin] == target[n.target]) {
				node no = n;
				no.step += c[0];
				while(origin[++no.origin] == target[++no.target]);
				if (judge(no)) break;
				q.push(no);
			}
			if(revert(n)) {
				node no = n;
				no.step += c[0];
				do {
					no.origin++;
					no.target++;
				} while(revert(no));
				if (judge(no)) break;
				q.push(no);
			}
		}
	}
	printf("%i", finally_done_step);
	return 0;
}

/*
3 2 3 CCGATGTATCTG TACGATCGGTC
*/
