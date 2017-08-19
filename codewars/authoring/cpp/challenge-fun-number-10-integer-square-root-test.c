#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXN 201

char *integerSquareRoot(char *str);
char *integerSquareRoot2(char *str);

Test(examples, should_pass_all_the_tests_provided) {
  cr_assert_eq(strcmp("1", integerSquareRoot("1")), 0);
  cr_assert_eq(strcmp("2", integerSquareRoot("5")), 0);
  cr_assert_eq(strcmp("4", integerSquareRoot("17")), 0);
  char *gg = integerSquareRoot("23232328323215435345345345343458098856756556809400840980980980980809092343243243243243098799634");
  cr_assert_eq(strcmp("152421548093487868711992623730429930751178496967", gg), 0);
  char *ret = integerSquareRoot("12323309809809534545458098709854808654685688665486860956865654654654324238000980980980");
  cr_assert_eq(strcmp("3510457208086937291253621317073222057793129", ret), 0);
  free(gg);
  free(ret);
}

Test(random_test, should_pass_all_tests) {
  srand((unsigned)time(0));
  int gg = 0;
  char ret[100], ret2[100], ret22[100];
  for (gg = 0; gg < 10; gg++) {
    int i;
    for (i = 0; i < 80; i++) {
      char ed = rand() % 10;
      if (!i && !ed) ed = 1;
      ret[i] = ret2[i] = ret22[i] = ed + '0';
    }
    ret[i] = ret2[i] = ret22[i] = 0;
    char *c = integerSquareRoot2(ret2);
    char *y = integerSquareRoot(ret);
    printf("testing for %s, the correct answer is %s, yours is %s\n", ret22, c, y);
    cr_assert_eq(strcmp(c, y), 0);
    free(c);
    free(y);
  }
}


char *bigN_sqrt2(char *s);
int  bigN_cmp2(char *a, char *b, int lim);
void bigN_mul2(char *a, int k, int lim);
void bigN_add2(char *a, int k);
void bigNN_minus2(char *a, char *b, int lim);
int  Newtonsqrt2(double x);

char *integerSquareRoot2(char *str) {
	return bigN_sqrt2(str);
}

int bigN_cmp2(char *a, char *b, int lim) {
	int i;
	for (i = lim - 1; i >= 0; --i)
		if (a[i] < b[i]) return 1;
		else if (a[i] > b[i]) return -1;
	return 0;
}

void bigN_mul2(char *a, int k, int lim) {
	int i, tmp, c;
	for (c = i = 0; i < lim; ++i) {
		tmp = a[i] * k + c;
		c = tmp / 10;
		a[i] = tmp - 10 * c;
	}
}
void bigN_add2(char *a, int k) {
	int i = 0;
	while (k > 0) {
		a[i++] += k % 10;
		k /= 10;
	}
}
void bigNN_minus2(char *a, char *b, int lim) {
	int i, tmp, c;
	for (c = i = 0; i < lim; ++i) {
		tmp = b[i] - a[i] + c;
		c = (tmp < 0 ? -1 : 0);
		b[i] = (tmp + 10) % 10;
	}
}

int Newtonsqrt2(double x) {
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

char *bigN_sqrt2(char *s) {
	short int i, k, slen;
	int lim;
	lim = slen = strlen(s);
	if (slen < 18) {
		double value = atof(s);
		char *ret = (char *) malloc(100 * sizeof(char));
		sprintf(ret, "%d", Newtonsqrt2(value));
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
	char *ret = (char *) malloc(slen * sizeof(char));;
	int ret_index = 0;
	while (1) {
		i = 0;
		while (1) {
			++i;
      int j;
      for (j = 0; j < MAXN; j++) {
        tmp[j] = res[j];
      }
			bigN_mul2(tmp, i * 20, lim);
			bigN_add2(tmp, i * i);
			if (-1 == bigN_cmp2(tmp, cur, lim)) break;
		}
		--i;
		ret[ret_index++] = i + '0';
    int j;
    for (j = 0; j < MAXN; j++) {
      tmp[j] = res[j];
    }
		bigN_mul2(tmp, i * 20, lim);
		bigN_add2(tmp, i * i);
		bigNN_minus2(tmp, cur, lim);

		bigN_mul2(res, 10, lim);
		bigN_add2(res, i);

		k += 2;
		if (k >= slen) break;
		else {
			bigN_mul2(cur, 100, lim);
			bigN_add2(cur, ((s[k] - 48) * 10 + (s[k + 1] - 48)));
		}
	}
  ret[ret_index] = 0;
	return ret;
}
