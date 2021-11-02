#include <stdio.h>
#include <math.h>

const int TRUE = 1;
const int FALSE = 0;

enum kind
  {
   EMPTYSET,
   NUMBERSET,
   UNIONSET,
   PAIRSET
  };

struct Set {
  kind k;
  int rank;
  int (*in)(struct Set*);
  Set* x;
  Set* y;
};

Set emptyset
= {
   EMPTYSET,
   0,
   [] (Set* sp) {
     return FALSE;  
   },
   NULL,
   NULL
};

Set numberset
= {
   NUMBERSET,
   -1,
   [] (Set* sp) {
     if (sp->k == EMPTYSET)
       return TRUE;
     else
       return FALSE; //Todo
   },
   NULL,
   NULL
};

struct Set unionset(Set* x) {
  Set set = {
    UNIONSET,
    (x->rank > 0) ? x->rank - 1 : x->rank,
    [] (Set* sp) {
      return FALSE; //Todo
    },
    x,
    NULL
  };

  return set;
}

struct Set pairset(Set* x, Set* y) {
  Set set = {
             PAIRSET,
             max(x->rank, y->rank) + 1,
             [] (Set* sp) {
               return FALSE; //Todo
             },
             x,
             y
  };

  return set;
}


int prompt(char* line) {
  int ret;
  printf("set-lang>");
  ret = scanf("%s", line);
  return ret;
}

int main() {
  char line[100];
  while(prompt(line) >= 0) {
    printf("%s\n", line);
  }
}
