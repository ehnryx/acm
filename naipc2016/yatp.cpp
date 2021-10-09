#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Line {
  mutable ll m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll b) {
    m = -m; b = -b;
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    auto l = *lower_bound(x);
    return -l.m * x + -l.b;
  }
};

const int N = 2e5 + 1;
int weight[N];
vector<pair<int, int>> adj[N];

ll ans[N];

bool vis[N];
int sz[N];

void get_dists(int u, int p, ll d, vector<pair<int, ll>>& have) {
  have.emplace_back(u, d);
  for(auto [v, c] : adj[u]) {
    if(v == p || vis[v]) continue;
    get_dists(v, u, d + c, have);
  }
}

void solve_block(int c) {
  vector<pair<int, ll>> have;
  get_dists(c, 0, 0, have);
  LineContainer lc;
  for(auto [v, d] : have) {
    lc.add(weight[v], d);
    //cerr << " lin " << v << " -> " << weight[v] << " " << d << nl;
  }
  for(auto [v, d] : have) {
    ans[v] = min(ans[v], lc.query(weight[v]) + d);
    //cerr << " upd " << v << " <- " << ans[v] << nl;
  }
}

int dfs(int u, int p, ll d, vector<int>& seen) {
  seen.push_back(u);
  sz[u] = 1;
  for(auto [v, c] : adj[u]) {
    if(v == p || vis[v]) continue;
    sz[u] += dfs(v, u, d + c, seen);
  }
  return sz[u];
}

int centroid(int u) {
  vector<int> seen;
  int s = dfs(u, 0, 0, seen);
  for(int v : seen) {
    if(2*sz[v] < s) continue;
    bool ok = true;
    for(auto [w, _] : adj[v]) {
      if(vis[w]) continue;
      if(sz[w] < sz[v] && 2*sz[w] > s) {
        ok = false;
        break;
      }
    }
    if(ok) {
      solve_block(v);
      return v;
    }
  }
  assert(false);
}

void solve(int u) {
  int c = centroid(u);
  vis[c] = true;
  for(auto [v, _] : adj[c]) {
    if(vis[v]) continue;
    solve(v);
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    cin >> weight[i];
  }
  for(int i=1; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  memset(ans, 0x3f, sizeof(ans));
  solve(1);

  ll sum = 0;
  for(int i=1; i<=n; i++) {
    sum += ans[i];
    //cerr << i << ": " << ans[i] << nl;
  }
  cout << sum << nl;

  return 0;
}
