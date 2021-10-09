#include <bits/stdc++.h>
using namespace std;

#define debug

#define nl '\n'
#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}

struct Monkey {
  int a, b;
  void insert(int a, int b) {
    this->a = a;
    this->b = b;
  }
  string solve() {
    if (a >= b) return "FunkyMonkeys";
    else return "WeWillEatYou";
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  Monkey monkeys;
  int a, b;
  int T;
  read(T);
  while (T--) {
    read(a); read(b);
    monkeys.insert(a, b);
    cout << monkeys.solve() << nl;
  }

  return 0;
}
