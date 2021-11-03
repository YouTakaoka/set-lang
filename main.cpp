#include <stdio.h>
#include <algorithm>

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
  std::function<bool (struct Set*)> in;
  Set* x;
  Set* y;
};

Set emptyset
= {
   EMPTYSET,
   0,
   [] (Set* sp) {
     return false;  
   },
   NULL,
   NULL
};

bool seteq(Set* x, Set* y) {
  return false; //Todo
}

Set numberset
= {
   NUMBERSET,
   -1,
   [] (Set* sp) {
     if (sp->k == EMPTYSET)
       return true;
     else
       return false; //Todo
   },
   NULL,
   NULL
};

struct Set unionset(Set* x) {
  Set set = {
    UNIONSET,
    (x->rank > 0) ? x->rank - 1 : x->rank,
    [x] (Set* sp) {
      return false; //Todo
    },
    x,
    NULL
  };

  return set;
}

struct Set pairset(Set* x, Set* y) {
  Set set = {
    PAIRSET,
    std::max(x->rank, y->rank) + 1,
    [x ,y] (Set* sp) {
      return sp == x || sp == y; //Todo
    },
    x,
    y
  };

  return set;
}


int main() {
  printf("main\n");
}
