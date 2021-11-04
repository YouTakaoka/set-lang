#include <iostream>
#include <functional>
#include <algorithm>

enum kind
  {
   EMPTYSET,
   NUMBERSET,
   UNIONSET,
   PAIRSET,
   SETMINUS,
   POWERSET,
   MIDSET
  };

struct Set {
  kind k;
  int rank;
  std::function<bool (struct Set*)> contains;
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

Set setminus(Set* x, Set* y) {
  return Set {
    SETMINUS,
    x->rank, //TO FIX
    [x, y] (Set* sp) {
      return x->contains(sp) && !y->contains(sp);
    },
    x,
    y
  };
}

bool isempty(Set* x) {
  return x->rank == 0;
}

Set powerset(Set* x) {
  return Set {
    POWERSET,
    x->rank + 1,
    [x] (Set* sp) {
      return setminus(sp, x).rank == 0;
    },
    x,
    NULL
  };
};

bool seteq(Set* x, Set* y) {
  return powerset(x).contains(y) && powerset(y).contains(x);
}

Set pairset(Set* x, Set* y) {
  return Set {
    PAIRSET,
    std::max(x->rank, y->rank) + 1,
    [x ,y] (Set* sp) {
      return seteq(sp, x) || seteq(sp, y);
    },
    x,
    y
  };
}

Set midset(Set* x, Set* y) {
  return Set {
    MIDSET,
    y->rank, //TO FIX
    [x, y] (Set* sp) {
      return x->contains(sp) && y->contains(sp);
    },
    x,
    y
  };
}

Set unionset(Set* x) {
  return Set {
    UNIONSET,
    (x->rank > 0) ? x->rank - 1 : x->rank,
    [x] (Set* sp) {
      Set m = midset(sp, x);
      return !isempty(&m);
    },
    x,
    NULL
  };
}

Set succ(Set* x) {
  Set p1 = pairset(x, x);
  Set p2 = pairset(x, &p1);
  return unionset(&p2);
}

Set numberset
= {
   NUMBERSET,
   -1,
   [] (Set* sp) {
     if (isempty(sp))
       return true;
     else if (sp->rank == -1)
       return false;

     Set u = unionset(sp);
     Set s = succ(&u);
     return seteq(sp, &s) && numberset.contains(&u);     
   },
   NULL,
   NULL
};

int main() {
  printf("main\n");
}
