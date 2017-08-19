#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXN 201

char *bigN_sqrt(char *s);
int  bigN_cmp(char *a, char *b, int lim);
void bigN_mul(char *a, int k, int lim);
void bigN_add(char *a, int k);
void bigNN_minus(char *a, char *b, int lim);
int  Newtonsqrt(double x);

char *integerSquareRoot(char *str) {
	return bigN_sqrt(str);
}

int bigN_cmp(char *a, char *b, int lim) {
	int i;
	for (i = lim - 1; i >= 0; --i)
		if (a[i] < b[i]) return 1;
		else if (a[i] > b[i]) return -1;
	return 0;
}

void bigN_mul(char *a, int k, int lim) {
	int i, tmp, c;
	for (c = i = 0; i < lim; ++i) {
		tmp = a[i] * k + c;
		c = tmp / 10;
		a[i] = tmp - 10 * c;
	}
}
void bigN_add(char *a, int k) {
	int i = 0;
	while (k > 0) {
		a[i++] += k % 10;
		k /= 10;
	}
}
void bigNN_minus(char *a, char *b, int lim) {
	int i, tmp, c;
	for (c = i = 0; i < lim; ++i) {
		tmp = b[i] - a[i] + c;
		c = (tmp < 0 ? -1 : 0);
		b[i] = (tmp + 10) % 10;
	}
}

int Newtonsqrt(double x) {
	double x1 = 1;
	double x2 = x1 / 2.0 + x / 2.0 / x1;
	while (fabs(x2 - x1) > 0.1) {
		x1 = x2;
		x2 = x1 / 2.0 + x / 2.0 / x1;
	}
	return floor(x1);
}

char res[MAXN];
char cur[MAXN];
char tmp[MAXN];

char *bigN_sqrt(char *s) {
	short int i, k, slen;
	int lim;
	lim = slen = strlen(s);
	if (slen < 18) {
		double value = atof(s);
		char *ret = (char *) malloc(100 * sizeof(char));
		sprintf(ret, "%d", Newtonsqrt(value));
		return ret;
	}
  for (i = 0; i < MAXN; i++) {
    res[i] = cur[i] = tmp[i] = 0;
  }

	if (slen & 0x1) {
		k = -1;
		cur[0] = s[0] - 48;
	} else {
		k = 0;
		cur[1] = s[0] - 48;
		cur[0] = s[1] - 48;
	}
	char *ret = (char *) malloc(slen * sizeof(char));
	int ret_index = 0;
	while (1) {
		i = 0;
		while (1) {
			++i;
      int j;
      for (j = 0; j < MAXN; j++) {
        tmp[j] = res[j];
      }
			bigN_mul(tmp, i * 20, lim);
			bigN_add(tmp, i * i);
			if (-1 == bigN_cmp(tmp, cur, lim)) break;
		}
		--i;
		ret[ret_index++] = i + '0';
    int j;
    for (j = 0; j < MAXN; j++) {
      tmp[j] = res[j];
    }
		bigN_mul(tmp, i * 20, lim);
		bigN_add(tmp, i * i);
		bigNN_minus(tmp, cur, lim);

		bigN_mul(res, 10, lim);
		bigN_add(res, i);

		k += 2;
		if (k >= slen) break;
		else {
			bigN_mul(cur, 100, lim);
			bigN_add(cur, ((s[k] - 48) * 10 + (s[k + 1] - 48)));
		}
	}
  ret[ret_index] = 0;
	return ret;
}
