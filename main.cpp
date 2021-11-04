#include <iostream>
#include <functional>
#include <algorithm>

struct Set {
  int rank;
  std::function<bool (struct Set*)> contains;
};

Set emptyset
= {
   0,
   [] (Set* sp) {
     return false;  
   }
};

Set setminus(Set* x, Set* y) {
  return Set {
    x->rank, //TO FIX
    [x, y] (Set* sp) {
      return x->contains(sp) && !y->contains(sp);
    }
  };
}

bool isempty(Set* x) {
  return x->rank == 0;
}

Set powerset(Set* x) {
  return Set {
    x->rank + 1,
    [x] (Set* sp) {
      return setminus(sp, x).rank == 0;
    }
  };
};

bool seteq(Set* x, Set* y) {
  return powerset(x).contains(y) && powerset(y).contains(x);
}

Set pairset(Set* x, Set* y) {
  return Set {
    std::max(x->rank, y->rank) + 1,
    [x ,y] (Set* sp) {
      return seteq(sp, x) || seteq(sp, y);
    }
  };
}

Set midset(Set* x, Set* y) {
  return Set {
    y->rank, //TO FIX
    [x, y] (Set* sp) {
      return x->contains(sp) && y->contains(sp);
    }
  };
}

Set unionset(Set* x) {
  return Set {
    (x->rank > 0) ? x->rank - 1 : x->rank,
    [x] (Set* sp) {
      Set m = midset(sp, x);
      return !isempty(&m);
    }
  };
}

Set succ(Set* x) {
  Set p1 = pairset(x, x);
  Set p2 = pairset(x, &p1);
  return unionset(&p2);
}

Set numberset
= {
   -1,
   [] (Set* sp) {
     if (isempty(sp))
       return true;
     else if (sp->rank == -1)
       return false;

     Set u = unionset(sp);
     Set s = succ(&u);
     return seteq(sp, &s) && numberset.contains(&u);     
   }
};

int main() {
  printf("main\n");
}
