#include <stdio.h>
//#include <iostream>
#include <string.h>

char in[101];

int main(int argc, char *argv[]) {
  long long i, row;
  int l;
  char asas, column;
  scanf("%s", in);
  l = strlen(in);
  column = in[l - 1];
  in[l - 1] = 0;
  sscanf(in, "%I64d", &row);
  i = (--row >> 2) << 4;
//  printf("%I64d\n", i);
  if (!(row & 1))
    switch (column) {
    case 'a':
      i += 4;
      break;
    case 'b':
      i += 5;
      break;
    case 'c':
      i += 6;
      break;
    case 'd':
      i += 3;
      break;
    case 'e':
      i += 2;
      break;
    case 'f':
      i += 1;
      break;
    }
  else
    switch (column) {
    case 'a':
      i += 11;
      break;
    case 'b':
      i += 12;
      break;
    case 'c':
      i += 13;
      break;
    case 'd':
      i += 10;
      break;
    case 'e':
      i += 9;
      break;
    case 'f':
      i += 8;
      break;
    }
  printf("%I64d", i);
  return 0;
}

/*
5e
10e
*/
