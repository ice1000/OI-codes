#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define avg ((idx1 + idx2) >> 1)
#define in1 while ((c = getchar()) == ' ')
#define in2 while ((c = getchar()) == '\n')
#define space (node*)malloc(sizeof(node))

struct node {
  char c;
  node *next;
  node *last;
} *root, *now, *next, *last, *idx1, *idx2;

//char seq[4000005];
// len: length
// pos1: position of idx1 (left cursor)
// pos2: position of idx2 (right cursor)
int len, pos1, pos2;

void show() {
  now = root;
  putchar(now->c);
  while (now = now->next) {
    // last is '\n'
    putchar(now->c);
  }
}

int main(int argc, char *argv[]) {
  freopen("editor.in", "r", stdin);
  //	freopen("editor.out", "w", stdout);
  int i, j, n, rooted = 0;
  char c;
  root = space;
  while ((c = getchar()) != '\n') {
    ++len;
    if (!rooted) {
      // бс
      root->c = c;
      root->next = NULL;
      root->last = NULL;
      now = root;
      ++rooted;
    } else {
      next = space;
      now->next = next;
      next->last = now;
      next->next = NULL;
      next->c = c;
      now = next;
    }
  }
  pos1 = 0;
  pos2 = len;
  last = space;
  last->c = '\n';
  last->last = now;
  last->next = NULL;
  now->next = last;
  idx1 = root;
  idx2 = last;
  scanf("%i", &n);
  while (n--) {
    in2;
    //		printf("command: %c\n", c);
    switch (c) {
    case '<':
      in1;
      if (c == 'L') {
	if (idx1->last) {
	  --pos1;
	  puts("T"), idx1 = idx1->last;
	} else puts("F");
      } else {
	if (idx2->last) {
	  --pos2;
	  puts("T"), idx2 = idx2->last;
	} else puts("F");
      }
      break;
    case '>':
      in1;
      if (c == 'L') {
	if (idx1->next != last) {
	  puts("T"), idx1 = idx1->next;
	  ++pos1;
	} else puts("F");
      } else {
	if (idx2->next != last) {
	  puts("T"), idx2 = idx2->next;
	  ++pos2;
	} else puts("F");
      }
      break;
    case 'I':
      in1;
      if (c == 'L') {
	if (pos2 >= pos1) ++pos2;
	// move
	++pos1;
	now = idx1->last;
	next = space;
	// setup
	in1;
	next->c = c;
	next->next = idx1;
	next->last = now;
	// redirect
	now->next = next;
	idx1->last = next;
      } else {
	if (pos1 >= pos2) ++pos1;
	++pos2;
	// move
	now = idx2->last;
	next = space;
	// setup
	in1;
	next->c = c;
	next->next = idx2;
	next->last = now;
	// redirect
	now->next = next;
	idx2->last = next;
      }
      puts("T");
      break;
    case 'D':
      in1;
      if (c == 'L') {
	if (idx1->next == NULL
	    //				|| idx1->next == last
	    ) {
	  puts("F");
	} else {
	  idx1->next->last = idx1->last;
	  idx1->next = idx1->next->next;
	  if (pos2 > pos1) --pos2;
	  puts("T");
	}
      } else {
	if (idx2->next == NULL
	    //				 || idx2->next == last
	    ) {
	  puts("F");
	} else {
	  idx2->next->last = idx2->last;
	  idx2->next = idx2->next->next;
	  if (pos1 > pos2) --pos1;
	  puts("T");
	}
      }
      break;
    case 'R':
      if (pos1 < pos2) {
	next = idx2->next;
	now = idx1->last;
	if (idx1 != NULL)
	  idx1->next = next;
	if (next != NULL)
	  next->last = idx1;
	if (idx2 != NULL)
	  idx2->last = now;
	if (now != NULL)
	  now->next = idx2;
	// exchange back
	now = idx1;
	idx1 = idx2;
	idx2 = now;
	int t = pos1;
	pos1 = pos2;
	pos2 = t;
	puts("T");
      } else {
	puts("F");
      }
      break;
    case 'S':
      show();
      break;
    }
    //		show();
    //		printf("pos1 = %i, pos2 = %i\n", pos1, pos2);
  }
  return 0;
}


/*
  goodykc
  11
  I R u
  I R l
  > L
  > L
  > L
  > L
  R
  D R
  < R
  D R
  S
*/
