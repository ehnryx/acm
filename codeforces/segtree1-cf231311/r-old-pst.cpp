#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
  ll v, lazy;
  int l, r;
  Node(ll v=0, ll z=0, int l=0, int r=0):
    v(v), lazy(z), l(l), r(r) {}
};

// N: a power of 2
// P: number of point updates
// R: number of range updates
template<int N, int P, int R>
struct PersistentSegmentTree {
  static constexpr int L = 32 - __builtin_clz(N);
  vector<int> root;
  vector<Node> segt;
  int idx;

  PersistentSegmentTree(ll v=0) {
    segt.resize(2*N);
    idx = 2*N;
    root.push_back(1);
    for (int i=N; i<2*N; i++) {
      segt[i] = Node(v);
    }
    for (int i=N-1; i>0; i--) {
      segt[i] = Node(v, 0, 2*i, 2*i+1);
    }
  }

  void pull(int i) {
    segt[i].v = min(segt[segt[i].l].v, segt[segt[i].r].v);
    segt[i].lazy = 0;
  }

  void setv(int x, ll v, int old=-1) {
    old = (old == -1 ? root.back() : root[old]);
    root.push_back(setv(x, v, old, 0, N-1));
  }
  int setv(int x, ll v, int old, int s, int e) {
    int cur = idx++;
    segt.push_back(Node(v));
    if (s == e) {
      return cur;
    }
    int m = (s+e)/2;
    if (x<=m) {
      segt[cur].l = setv(x, v, segt[old].l, s, m);
      segt[cur].r = segt[old].r;
    } else {
      segt[cur].l = segt[old].l;
      segt[cur].r = setv(x, v, segt[old].r, m+1, e);
    }
    pull(cur);
    return cur;
  }

  void update(int l, int r, ll v, int old=-1) {
    old = (old == -1 ? root.back() : root[old]);
    root.push_back(update(l, r, v, 0, old, 0, N-1));
  }
  int update(int l, int r, ll v, ll lazy, int old, int s, int e) {
    if (r<s || e<l) return old;
    int cur = idx++;
    assert(cur == segt.size());
    segt.push_back(Node(segt[old].v + lazy + v, segt[old].lazy + lazy + v, segt[old].l, segt[old].r));
    if (l<=s && e<=r) {
      return cur;
    }
    int m = (s+e)/2;
    segt[cur].l = update(l, r, v, segt[old].lazy + lazy, segt[old].l, s, m);
    segt[cur].r = update(l, r, v, segt[old].lazy + lazy, segt[old].r, m+1, e);
    pull(cur);
    return cur;
  }

  ll query(int l, int r, int version=-1) {
    version = (version == -1 ? root.back() : root[version]);
    return query(l, r, 0, version, 0, N-1);
  }
  ll query(int l, int r, ll lazy, int cur, int s, int e) {
    if (r<s || e<l) return INFLL;
    if (l<=s && e<=r) {
      return segt[cur].v + lazy;
    }
    int m = (s+e)/2;
    return min(
      query(l, r, lazy + segt[cur].lazy, segt[cur].l, s, m),
      query(l, r, lazy + segt[cur].lazy, segt[cur].r, m+1, e)
    );
  }

  void update_range(int l, int r, ll v) {
    if (l > r) {
      update(l, N-1, v);
      update(0, r, v);
    } else {
      update(l, r, v);
    }
  }

  ll query_range(int l, int r) {
    if (l > r) {
      return min(query(l, N-1), query(0, r));
    } else {
      return query(l, r);
    }
  }
};

const int M = 2e5+1;
PersistentSegmentTree<(1<<18), M, 2*M> segt(INFLL);

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  segt.update_range(0, (1<<18)-1, INFLL);

  int n;
  cin >> n;
  For(i,n) {
    int v;
    cin >> v;
    segt.setv(i, v);
  }

  int m;
  cin >> m;
  string line;
  getline(cin, line);
  For(i,m) {
    getline(cin, line);
    istringstream in(line);
    vector<int> q;
    for (int v; in >> v; ) {
      q.push_back(v);
    }
    if (q.size() == 2) {
      cout << segt.query_range(q[0],q[1]) << nl;
    } else {
      segt.update_range(q[0],q[1],q[2]);
    }
  }

  return 0;
}
