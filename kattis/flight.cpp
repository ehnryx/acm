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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Max {
  pair<int,int> a, b, c;
  Max() = default;
  void push(pair<int,int> u) {
    if(u > a) { c = b; b = a; a = u; }
    else if(u > b) { c = b; b = u; }
    else if(u > c) { c = u; }
  }
  int sum(int x=-1) const {
    int all = a.first + b.first + c.first;
    if(a.second == x) all -= a.first;
    else if(b.second == x) all -= b.first;
    else all -= c.first;
    return all;
  }
  int best(int x=-1) const {
    return (a.second == x ? b.first : a.first);
  }
};

const int N = 2500 + 1;
vector<int> adj[N];
int dp[N], up[N], par[N];
Max to[N];

void solve_dp(int u, int p) {
  par[u] = p;
  int cmax = 0;
  for(int v : adj[u]) {
    if(v == p) continue;
    solve_dp(v, u);
    to[u].push(pair(to[v].best() + 1, v));
    dp[u] = max(dp[u], dp[v]);
    up[v] = max(up[v], cmax);
    cmax = max(cmax, dp[v]);
  }
  dp[u] = max(dp[u], to[u].sum());

  cmax = 0;
  for(int i=(int)adj[u].size()-1; i>=0; i--) {
    if(adj[u][i] == p) continue;
    up[adj[u][i]] = max(up[adj[u][i]], cmax);
    cmax = max(cmax, dp[adj[u][i]]);
  }
}

void solve_up(int u, int p) {
  if(p) {
    up[u] = max(up[u], up[p]);
    up[u] = max(up[u], to[p].sum(u));
    to[u].push(pair(to[p].best(u) + 1, p));
  }
  for(int v : adj[u]) {
    if(v == p) continue;
    solve_up(v, u);
  }
}

int get_far(int s) {
  int last = s;
  queue<pair<int,int>> bfs;
  bfs.emplace(last, 0);
  while(!bfs.empty()) {
    auto [u, p] = bfs.front();
    bfs.pop();
    last = u;
    for(int v : adj[u]) {
      if(v != p) {
        bfs.emplace(v, u);
      }
    }
  }
  return last;
}

int center(int s) {
  s = get_far(s);
  memset(par, -1, sizeof par);
  pair<int,int> last(s, 0);
  queue<pair<int,int>> bfs;
  bfs.push(last);
  par[s] = 0;
  while(!bfs.empty()) {
    auto [u, d] = bfs.front();
    bfs.pop();
    last = pair(u, d);
    for(int v : adj[u]) {
      if(par[v] == -1) {
        par[v] = u;
        bfs.emplace(v, d + 1);
      }
    }
  }
  for(int i=0; i<last.second/2; i++) {
    last.first = par[last.first];
  }
  return last.first;
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
  vector<pair<int,int>> edges;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    edges.emplace_back(a, b);
  }
  solve_dp(1, 0);
  solve_up(1, 0);

  tuple<int,int,int> best(INF, 0, 0);
  for(auto [a, b] : edges) {
    if(a == par[b]) swap(a, b);
    int diam = max((dp[a] + 1) / 2 + (up[a] + 1) / 2 + 1, max(dp[a], up[a]));
    best = min(best, tuple(diam, a, b));
  }

  int a = get<1>(best);
  int b = get<2>(best);
  adj[a].erase(find(adj[a].begin(), adj[a].end(), b));
  adj[b].erase(find(adj[b].begin(), adj[b].end(), a));

  cout << get<0>(best) << nl;
  cout << a << " " << b << nl;
  cout << center(a) << " " << center(b) << nl;

  return 0;
}
