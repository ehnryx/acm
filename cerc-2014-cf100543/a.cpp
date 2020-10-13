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

struct Matching {
  vector<int> adj;
  vector<pair<int,int>> memo;
  Matching(int n) {
    adj.resize(n);
    memo.resize(1<<n, make_pair(-1, -1));
  }
  void add_edge(int a, int b) {
    adj[a] |= 1<<b;
    adj[b] |= 1<<a;
  }
  pair<int,int> solve(int n, int bm) {
    if(memo[bm].first != -1) return memo[bm];
    pair<int,int> res = make_pair(0, bm);
    for(int i=0; i<n; i++) {
      if(!(bm & 1<<i)) continue;
      for(int j=0; j<i; j++) {
        if(!(bm & 1<<j) || !(adj[i] & 1<<j)) continue;
        auto [val, unused] = solve(n, bm ^ 1<<i ^ 1<<j);
        if(res.first == val + 1) {
          res.second |= unused;
        } else {
          res = max(res, make_pair(val + 1, unused));
        }
      }
    }
    return memo[bm] = res;
  }
};

const int N = 1e3 + 1;
const int L = 10;
vector<int> adj[N];
vector<pair<int,int>> query[N];
set<int> reach[N];
int sz[N], depth[N], anc[N][L];

void build(int u, int p) {
  depth[u] = depth[p] + 1;
  anc[u][0] = p;
  for(int j=1; j<L; j++) {
    anc[u][j] = anc[anc[u][j-1]][j-1];
  }
  sz[u] = 1;
  auto parent = find(adj[u].begin(), adj[u].end(), p);
  if(parent != adj[u].end()) adj[u].erase(parent);
  for(int v : adj[u]) {
    build(v, u);
    sz[u] += sz[v];
  }
}

int lca(int a, int b) {
  if(depth[a] < depth[b]) swap(a, b);
  for(int j=L-1; j>=0; j--) {
    if(depth[anc[a][j]] >= depth[b]) {
      a = anc[a][j];
    }
  }
  if(a == b) return a;
  for(int j=L-1; j>=0; j--) {
    if(anc[a][j] != anc[b][j]) {
      a = anc[a][j];
      b = anc[b][j];
    }
  }
  return anc[a][0];
}

int solve(int u) {
  int res = 0;
  for(int v : adj[u]) {
    res += solve(v);
  }

  int n = adj[u].size();
  Matching m(n);
  int bm = (1<<n) - 1;
  for(auto [a, b] : query[u]) {
    int s = (a == u ? n : -1);
    int t = (b == u ? n : -1);
    for(int i=0; i<n; i++) {
      if(reach[adj[u][i]].count(a)) {
        s = i;
      }
      if(reach[adj[u][i]].count(b)) {
        t = i;
      }
    }

    if(s == -1 || t == -1) continue;
    if(s == n) s = t;
    if(t == n) t = s;
    if(s != t) {
      m.add_edge(s, t);
    } else if(bm & 1<<s) {
      res++;
      bm ^= 1<<s;
    }
  }

  auto [size, unused] = m.solve(n, bm);
  for(int i=0; i<n; i++) {
    if(!(unused & 1<<i)) continue;
    reach[u].insert(reach[adj[u][i]].begin(), reach[adj[u][i]].end());
  }
  reach[u].insert(u);
  return res + size;
}

void case_solve() {
  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    adj[i].clear();
    query[i].clear();
    reach[i].clear();
  }

  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  build(1, 0);

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    int c = lca(a, b);
    query[c].emplace_back(a, b);
    assert(c);
  }
  cout << solve(1) << nl;
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
    case_solve();
  }

  return 0;
}
