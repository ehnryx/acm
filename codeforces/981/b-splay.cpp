#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct SplayTree {
  vector<int> l, r, p, key, val, sum;
  int null, nsz, root;
  SplayTree(int n): null(n), nsz(0) {
    l.resize(n+1, null);
    r.resize(n+1, null);
    p.resize(n+1, null);
    key.resize(n+1, 0);
    val.resize(n+1, 0);
    sum.resize(n+1, 0);
    root = null;
  }

  void insert(int x, int v) {
    key[nsz] = x;
    sum[nsz] = val[nsz] = v;
    if (nsz) {
      find(x);
      if (l[x] != null) p[l[x]] = nsz;
      p[x] = nsz;
      l[nsz] = l[x];
      r[nsz] = x;
      l[x] = null;
      // TODO fix
    }
    nsz++;
  }

  void splay(int x) {
    push(x);
    while (p[x] != null) {
      if (l[l[p[p[x]]]] == x || r[r[p[p[x]]]] == x) lift(p[x]);
      else lift(x);
    }
    root = x;
  }

  void push(int x) {
    // TODO
  }

  void update(int x) {
    if (x == null) return;
    sum[x] = sum[l[x]] + sum[r[x]];
  }

  void lift(int x) {
    if (p[x] == null) return;
    push(p[x]); push(x); push(l[x]); push(r[x]);
    vector<int>& a = (l[p[x]] == x ? l : r);
    vector<int>& b = (l[p[x]] == x ? r : l);
    if (b[x] != null) p[b[x]] = p[x];
    swap(p[x], b[x]);
    swap(p[x], a[b[x]]);
    swap(p[x], p[b[x]]);
    update(a[b[x]]);
    update(b[x]);
    update(x);
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  SplayTree ans(2e5+1);

  int n, a, x;
  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> a >> x;
    ans.insert(a,x);
  }

  int m, b, y;
  cin >> m;
  for (int i=0; i<m; i++) {
    cin >> b >> y;
    ans.update(b,y);
  }

  cout << ans.query() << nl;

  return 0;
}
