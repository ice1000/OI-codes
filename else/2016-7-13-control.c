#include <stdio.h>
#include <string.h>

struct {
	short percentage;
	short control;
} a[1005][1005];

int i, j, k, data_total, company_total;
short h, s, p, save;

int max (int, int);

int main (int argc, char *argv[]) {
	freopen("control.in", "r", stdin);
	freopen("control.out", "w+", stdout);
	memset(a, 0, sizeof(a));
	scanf("%i", &data_total);
	for ( i = 0; i < data_total; ++i ) {
		scanf("%hi %hi %hi", &h, &s, &p);
		a[h][s].percentage = p;
		company_total = max(company_total, h);
		company_total = max(company_total, s);
	}
	for ( i = 1; i <= data_total; i++ ) {
		for ( j = 1; j <= data_total; j++ ) {
			if ( i == j ) continue;
			// if i can control j
			if ( a[i][j].percentage > 50 ) {
				a[i][j].control++;
				continue;
			}
			// put the original control of k to save[k]
			save = a[i][j].percentage;
			// if i's controlled company k can control j
			for ( k = 1; k <= company_total; ++k ) {
				if ( a[i][k].control ) {
					save += a[k][j].percentage;
				}
			}
			if ( save > 50 )
				a[i][j].control++;
		}
	}
	for ( i = 1; i <= company_total; i++ ) {
		for ( j = 1; j <= company_total; ++j ) {
			if ( a[i][j].control && i != j) {
				printf("%i %i\n", i, j);
			}
		}
	}
	return 0;
}

int max (int x, int y) {
	return x > y ? x : y;
}
/*
3
1 2 80
2 3 80
3 1 20
 */

