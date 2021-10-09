#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const char nl = '\n';
const ld EPS = 1e-19L;
const ld EPS2 = 1e-42L;

// MAGIC IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
template <typename T> inline void read(T &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

const int N = 1e6+1;

struct Line {
  ld m, b, s;
} lines[N];

struct LineContainer {
  int pos, sz;
  LineContainer() : pos(0), sz(0) {}
  ld isect(const Line& v, ld m, ld b) {
    return (v.b - b) / (m - v.m);
  }
  void add(const ld& m, const ld& b) {
    while(sz>0) {
      ld x = isect(lines[sz-1], m, b);
      if(x > lines[sz-1].s) {
        lines[sz++] = {m,b,x};
        pos = min(pos, sz-1);
        return;
      }
      sz--;
    }
    lines[sz++] = {m,b,0};
    pos = 0;
  }
  ld query(ld x) {
    while(pos+1 < sz && lines[pos+1].s < x) {
      pos++;
    }
    return lines[pos].m * x + lines[pos].b;
  }
};

const int D = 1e6;
ld pval[N], sval[N];

ld solve(int l, int r) {
  if(l == r) {
    return pval[r]*sval[r];
  }

  int m = (l+r)/2;
  ld res = max(solve(l, m), solve(m+1, r));

  int lb = m;
  for(ld curp = 1; lb > l && curp > EPS; lb--) {
    curp *= pval[lb];
  }

  LineContainer hull;
  ld prod = 1;
  ld sum = 0;
  hull.add(1/prod, -sum/prod);
  for(int i=lb; i<=r && prod > EPS2; i++) {
    prod *= pval[i];
    sum += sval[i];
    res = max(res, prod * hull.query(sum));
    hull.add(1/prod, -sum/prod);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(0);

  freopen("cowdate.in", "r", stdin);
  freopen("cowdate.out", "w", stdout);

  int n;
  read(n);
  for(int i=1; i<=n; i++) {
    int a;
    read(a);
    ld pass = (ld)a/D;
    ld fail = 1 - pass;
    pval[i] = fail;
    sval[i] = pass / fail;
  }
  ld ans = solve(1, n);
  cout << floor(D*ans) << nl;

  return 0;
}
