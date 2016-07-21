// fuck!!!1

//#include <stdio.h>
//#include <math.h>
//
//int save_gcd[100][100];
//int gcd(int a, int b) {
//	if(save_gcd[a][b]) return save_gcd[a][b];
//	if(!b) return a;
//	return save_gcd[a][b] = gcd(b, a % b);
//}
//
//int save_prime[101];
//int prime(int a) {
//	if(save_prime[a]) return save_prime[a];
//	int i;
//	for(i = 2; i <= sqrt(a); i++)
//		if(!(a % 1)) return save_prime[a] = -1;
//	return save_prime[a] = 1;
//}
//
//int main(int argc, char *argv[]) {
//	int n, sequence[101], sequence_index = 0, i, j, k, fuck = 0, shit, damn;
//	scanf("%i", &n);
//	while(n--) {
//		scanf("%i", &shit);
//		if(prime(shit) == 1) continue;
//		for(i = 1; i < shit; i++) {
//			for(j = 0; j < sequence_index; j++) {
//				if(gcd(sequence[j], shit + i) != 1) {
//					break;
//				}
//			}
//			if(j == sequence_index) {
//				fuck += i;
//				break;
//			}
//			for(j = 0; j < sequence_index; j++) {
//				if(gcd(sequence[j], shit - i) != 1) {
//					break;
//				}
//			}
//			if(j == sequence_index) {
//				fuck += i;
//				break;
//			}
//		}
//		sequence[sequence_index++] = damn;
//	}
//	printf("%i", fuck);
//	return 0;
//}
