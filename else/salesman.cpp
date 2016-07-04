//#include <stdio.h>
//#include <memory.h>
//#include <queue>
//using namespace std;
//
//typedef struct {
//	int c;
//	int s;
//	int d[15];
//} node ;
//
//int main(int argc, char* argv[]) {
//	int i, j, n, s[15][15], ret = 0xFFF;
//	node f;
//	queue<node> q;
//	scanf("%d", &n);
//	for(i = 0; i < n; i++) {
//		for(j = 0; j < n; j++) {
//			scanf("%d", &s[i][j]);
//		}
//	}
//	while(!q.empty()) q.pop();
//	f.c = 0;
//	f.s = 0;
//	memset(f.d, 0, n * sizeof(f.d[0]));
//	f.d[0] = 1;
////	q.push(f);1
////	while(!q.empty()) {
////		node b = q.front();
////		if(b.c == n - 1) {
////			ret = min(ret, b.s);
////			break;
////		}
////		for(i = 0; i < n; j++) {
////			// 1、不能重复 2、不能自己走自己
////			if(!b.d[i] && i != b.c) {
////				node m;
////				m.s = b.s + s[b.c][i];
////				for(j = 0; j < n; j++) {
////					m.d[j] = b.d[j];
////				}
////				m.d[b.c] = 1;
////			}
////		}
////	}
//	printf("%d", ret);
//	return 0;
//}
