//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

// Persistent Segment Tree
namespace PST {
  const int D = 3e7;

  int sid;
  int st[D];
  int ls[D], rs[D];

  void pull(int ver) {
    st[ver] = st[ls[ver]] + st[rs[ver]];
  }

  void insert(int& ver, int old, int v, int x, int s, int e) {
    ver = ++sid;
    ls[ver] = ls[old];
    rs[ver] = rs[old];
    st[ver] = st[old];

    if(s == e) {
      st[ver] = v;
      return;
    }

    int m = (s+e) / 2;
    if(x<=m) insert(ls[ver], ls[old], v, x, s, m);
    else insert(rs[ver], rs[old], v, x, m+1, e);
    pull(ver);
  }

  int query(int ver, int l, int r, int s, int e) {
    if(r<s || e<l) return 0;
    if(l<=s && e<=r) {
      return st[ver];
    }

    int m = (s+e) / 2;
    return query(ls[ver], l, r, s, m) + query(rs[ver], l, r, m+1, e);
  }
}

const int M = 1e5 + 7;
int A[M], B[M], C[M];

const int N = 1e3 + 1;
vector<int> adj[N];

pair<int,int> find(int s, int t, int p) {
  if(s == t) return make_pair(-1, -1);
  for(int e : adj[s]) {
    int v = s ^ A[e] ^ B[e];
    if(v == p) continue;
    auto res = find(v, t, s);
    if(res.first) return max(res, make_pair(C[e], e));
  }
  return make_pair(0, 0);
}

void solve_case() {
  int n, m;
  cin >> n >> m;

  const int PSTN = (m <= 1 ? 1 : 1 << (32 - __builtin_clz(m-1)));
  for(int i=1; i<=n; i++) {
    adj[i].clear();
  }
  PST::sid = 0;

  vector<pair<int,int>> edges;
  for(int i=0; i<m; i++) {
    cin >> A[i] >> B[i] >> C[i];
    edges.emplace_back(C[i], i);
  }
  sort(edges.begin(), edges.end(), greater<pair<int,int>>());

  map<int,int> root, index;
  multiset<int> have;
  vector<int> order(m);
  root[0] = 0;
  for(int k=0, cur=0; k<m; k++) {
    auto [c, i] = edges[k];
    order[i] = k;
    index[c] = k;

    auto [cost, r] = find(A[i], B[i], 0);
    if(cost) {
      have.erase(have.find(cost));
      adj[A[r]].erase(find(adj[A[r]].begin(), adj[A[r]].end(), r));
      adj[B[r]].erase(find(adj[B[r]].begin(), adj[B[r]].end(), r));
      PST::insert(cur, cur, 0, order[r], 0, PSTN-1);
    }

    have.insert(c);
    adj[A[i]].push_back(i);
    adj[B[i]].push_back(i);
    PST::insert(cur, cur, c, order[i], 0, PSTN-1);
    root[c] = cur;

    //cerr << "TREE after " << k << nl; for(int i=1; i<=n; i++) {
    //cerr << "node " << i << ": "; for(int e : adj[i]) {
    //cerr << "(" << (i^A[e]^B[e]) << " , " << C[e]<<")  "; }
    //cerr << nl; }
  }
  root[INF] = 0;
  index[INF] = -1;

  int q;
  cin >> q;
  int last = 0;
  while(q--) {
    int l, r;
    cin >> l >> r;
    l -= last;
    r -= last;
    //cerr << "Query: " << l << " " << r << nl;

    int ver = root.lower_bound(l)->second;
    int left = index.upper_bound(r)->second + 1;
    //cerr << "version of: " << root.lower_bound(l)->first << nl;
    //cerr << "left: " << left << nl;
    last = PST::query(ver, left, PSTN-1, 0, PSTN-1);
    cout << last << nl;
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    solve_case();
  }

  return 0;
}

// 50 mins
