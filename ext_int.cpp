#include <iostream>

using namespace std;

enum ExtIntKind {EXT_INT_INTEGER,
                 EXT_INT_INF,
                 EXT_INT_MINF,
                 EXT_INT_UNDEF};

struct ExtInt {
  int val;
  ExtIntKind kind;

  ExtInt(ExtIntKind k, int v) {
    val = v;
    kind = k;
  }

  ExtInt(int v) {
    val = v;
    kind = EXT_INT_INTEGER;
  }

  string to_str() {
    switch(this->kind) {
    case EXT_INT_INTEGER:
      return to_string(this->val);
    case EXT_INT_INF:
      return "INF";
    case EXT_INT_MINF:
      return "MINF";
    case EXT_INT_UNDEF:
      return "UNDEF";
    default:
      return "ERROR";
    }
  }

  static ExtInt undef() {
    return ExtInt(EXT_INT_UNDEF, 0);
  }

  static ExtInt inf() {
    return ExtInt(EXT_INT_INF, 0);
  }

  static ExtInt minf() {
    return ExtInt(EXT_INT_MINF, 0);
  }

  ExtInt operator - () {
    switch(this->kind) {
    case EXT_INT_UNDEF:
      return undef();
    case EXT_INT_INTEGER:
      return ExtInt(- this->val);
    case EXT_INT_INF:
      return minf();
    case EXT_INT_MINF:
      return inf();
    }
  }
  
  ExtInt operator + (int i) {
    return ExtInt(this->kind, this->val + i);
  }

  ExtInt operator + (ExtInt ei) {
    switch(ei.kind) {
    case EXT_INT_UNDEF:
      return undef();
    case EXT_INT_INTEGER:
      return ExtInt(this->kind, this->val + ei.val);
    case EXT_INT_INF:
      switch(this->kind) {
      case EXT_INT_UNDEF:
      case EXT_INT_MINF:
        return undef();
      default:
        return inf();
      }
    case EXT_INT_MINF:
      return -(- *this + inf());
    }
  }

  ExtInt operator = (int i) {
    this->val = i;
    this->kind = EXT_INT_INTEGER;
    return *this;
  }
};

const ExtInt INF = ExtInt::inf();
const ExtInt MINF = ExtInt::minf();
const ExtInt UNDEF = ExtInt::undef();

ostream& operator<<(ostream& os, ExtInt ei) {
  os << ei.to_str();
  return os;
}

int main() {
  cout << INF << endl;
  cout << MINF << endl;
  cout << UNDEF << endl;
  cout << ExtInt(0) << endl;
}
