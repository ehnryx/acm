#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

#define PUSH 0
#define POP 1
#define ADD 2
#define XOR 3
#define MOV 4
#define RND 1000

struct inst {
  int type;
  int a1, a2;
};

int N;

inst parseline(string s) {
  istringstream in(s);
  string a; in >> a;
  string b, c; in >> b >> c;
  int type = ADD;
  int a1, a2 = -1e9;
  switch (a[0]) {
  case 'M':
    type = MOV;
  case 'A':
    a1 = -stoi(b.substr(1, b.size()), 0, 16);
    if (c[0] == 'R')
      a2 = -stoi(b.substr(1, b.size()), 0, 16);
    else a2 = stoi(b, 0, 16);
    break;
  case 'X':
    type = XOR;
    a1 = -stoi(b.substr(1, b.size()), 0, 16);
    if (c[0] == 'R')
      a2 = -stoi(b.substr(1, b.size()), 0, 16);
    else a2 = stoi(b, 0, 16);
    break;
  default:
    if (a[1] == 'U') {
      type = PUSH;
      a1 = -stoi(b.substr(1, b.size()), 0, 16);
    } else {
      type = POP;
      a1 = -stoi(b.substr(1, b.size()), 0, 16);
    }
  }
  return {type, a1, a2};
}
  
  


bool isConst(int pos) {
  (!(pos + insts.size() ))
  return insts[pos].a2 >= 0;
}

bool isMov2(int pos) {
  return (insts[pos].type == PUSH && insts[pos+1].type == POP && !isConst(pos+1));
}
bool isMovC(inst pos) {
  return (insts[pos].type == XOR && insts[pos].a1 == insts[pos].a2 
      && insts[pos+1].type == ADD && isConst(pos+1));
}

bool isAdd2(int pos) {
  return (
    (insts[pos].type == PUSH)
    && (insts[pos+1].type == MOV && !isConst(pos+1))
    && (insts[pos+2].type == ADD && !isConst(pos+2))
    && (insts[pos+3].type == POP)
    && (insts[pos].a1 == insts[pos+1].a1 && insts[pos+2].a2 == insts[pos].a1 && insts[pos+3].a1 == insts[pos].a1)
    && (insts[pos+2].a1 != insts[pos].a1)
  );
}
bool isAddC(int pos) {
  return (
    (insts[pos].type == PUSH)
    && (insts[pos+1].type == MOV && isConst(pos+1))
    && (insts[pos+2].type == ADD && !isConst(pos+2))
    && (insts[pos+3].type == MOV && !isConst(pos+3))
    && (insts[pos+4].type == POP)

    && (insts[pos].a1 == insts[pos+1].a1)
    && (insts[pos].a1 == insts[pos+2].a1)
    && (insts[pos].a1 == insts[pos+3].a2)
    && (insts[pos].a1 == insts[pos+4].a1)

    && (insts[pos+2].a1 != insts[pos+2].a2)
  );
}
bool isXor2(int pos) {
  return (
    (insts[pos].type == PUSH)
    && (insts[pos+1].type == MOV && !isConst(pos+1))
    && (insts[pos+2].type == XOR && isConst(pos+2))
    && (insts[pos+3].type == XOR && !isConst(pos+3))
    && (insts[pos+4].type == MOV && isConst(pos+4))
    && (insts[pos+5].type == XOR && !isConst(pos+5))
    && (insts[pos+6].type == POP)

    && (insts[pos].a1 == insts[pos+1].a1)
    && (insts[pos].a1 == insts[pos+2].a1)
    && (insts[pos].a1 == insts[pos+3].a2)
    && (insts[pos].a1 == insts[pos+4].a1)
    && (insts[pos].a1 == insts[pos+5].a2)
    && (insts[pos].a1 == insts[pos+6].a1)
    && (insts[pos+3].a1 == insts[pos+5].a1)

    && (insts[pos].a1 != insts[pos+3].a1)

    && (insts[pos+2].a2 == insts[pos+4].a2) // rndConst
  );
}

bool isXorC(int pos) {
  return (
    (insts[pos].type == PUSH)
    && (insts[pos+1].type == XOR && isConst(pos+1))
    && (insts[pos+2].type == XOR && !isConst(pos+2))
    && (insts[pos+3].type == POP)
    && (insts[pos+4].type == XOR && !isConst(pos+4))

    && (insts[pos].a1 == insts[pos+1].a1)
    && (insts[pos].a1 == insts[pos+2].a2)
    && (insts[pos].a1 == insts[pos+3].a1)
    && (insts[pos].a1 == insts[pos+4].a2)

    && (insts[pos+2].a1 == insts[pos+4].a1)

    && (insts[pos].a1 != insts[pos+2].a1)
  );
}

bool isPush(int pos) {
  return (
    (insts[pos].type == PUSH)
    && (insts[pos+1].type == MOV && !isConst(pos+1))
    && (insts[pos+2].type == POP)
    && (insts[pos+3].type == PUSH)
    && (insts[pos+4].type == XOR && !isConst(pos+4))
    && (insts[pos+5].type == XOR && !isConst(pos+5))
    && (insts[pos+6].type == XOR && !isConst(pos+6))

    && (insts[pos].a1 == insts[pos+1].a1)
    && (insts[pos].a1 == insts[pos+4].a1)
    && (insts[pos].a1 == insts[pos+5].a2)
    && (insts[pos].a1 == insts[pos+6].a1)

    && (insts[pos+1].a2 == insts[pos+2].a1)
    && (insts[pos+1].a2 == insts[pos+3].a1)
    && (insts[pos+1].a2 == insts[pos+4].a2)
    && (insts[pos+1].a2 == insts[pos+5].a1)
    && (insts[pos+1].a2 == insts[pos+6].a2)

    && (insts[pos+1].a1 != insts[pos+1].a2)
  );
}

bool isPush(int pos) {
  return (
    (insts[pos].type == MOV && !isConst(pos))
    && (insts[pos+1].type == POP)
    && (insts[pos+2].type == XOR && !isConst(pos+2))
    && (insts[pos+3].type == XOR && !isConst(pos+3))
    && (insts[pos+4].type == XOR && !isConst(pos+4))

    && (insts[pos].a1 == insts[pos+2].a1)
    && (insts[pos].a1 == insts[pos+3].a2)
    && (insts[pos].a1 == insts[pos+4].a1)

    && (insts[pos].a2 == insts[pos+1].a1)
    && (insts[pos].a2 == insts[pos+2].a2)
    && (insts[pos].a2 == insts[pos+3].a1)
    && (insts[pos].a2 == insts[pos+4].a2)
    
    && (insts[pos].a2 != insts[pos+2].a1)
  );
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif



  return 0;
}
