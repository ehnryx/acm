#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int I = 150;
const int MAXI = I+1;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct Edge {
  int a, b, c;
  bool operator < (const Edge& e) const {
    return c < e.c;
  }
};

const int N = I*1e5+1;
int root[N], sz[N];
int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}
inline bool link(int i, int j) {
  i = find(i); j = find(j);
  if (i==j) return false;
  if (sz[i] > sz[j]) swap(i,j);
  sz[i] += sz[j];
  root[j] = i;
  return true;
}

inline int get() {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int& x) {
  static char c; x = 0;
  for (c = get(); c < '0' || c > '9'; c = get());
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, m, ee;
  read(n); read(m); read(ee);

  vector<Edge> edges;
  for (int i=0; i<ee; i++) {
    int a, b, c;
    read(a); read(b); read(c);
    --a; --b;
    edges.push_back({a,b,c});
  }
  sort(edges.begin(), edges.end());

  ll ans[MAXI];
  int j;
  for (j=2; j<=I && clock()<2.89*CLOCKS_PER_SEC; j++) {
    memset(root, -1, n*j*sizeof(root[0]));
    memset(sz, -1, n*j*sizeof(sz[0]));
    ans[j] = 0;
    for (const Edge& e : edges) {
      for (int k=1; k<j; k++) {
        ans[j] += e.c * link(j*e.a+k, j*e.b+k-1);
      }
    }
  }
  //cerr << j << " iters" << nl;

  int II = j-1;
  for (int k=1; k<=min(m,II-3); k++) {
    cout << ans[k+1] << nl;
  }
  ll cur = ans[II-1];
  ll diff = ans[II]-ans[II-1];
  for (int k=min(m,II-3)+1; k<=m; k++) {
    cout << cur << nl;
    cur += diff;
  }

  return 0;
}
