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

const int N = 3e5 + 1;
vector<int> adj[N];
int par[N];

void build(int u, int p) {
  par[u] = p;
  if(p) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
  for(int v : adj[u]) {
    build(v, u);
  }
}

void rebuild(int u) {
  for(int v : adj[u]) {
    rebuild(v);
  }
  if(par[u]) adj[u].push_back(par[u]);
}

struct Max2 {
  int a, b;
  Max2(): a(0), b(-INF) {}
  void push(int v) {
    if(v > a) {
      b = a;
      a = v;
    } else if(v > b) {
      b = v;
    }
  }
};

int dp[N], up[N];
vector<int> prep[N], sufp[N];
Max2 maxdown[N], maxup[N];
vector<Max2> pre[N], suf[N];

void solve_down(int u) {
  for(int v : adj[u]) {
    solve_down(v);
    dp[u] = max(dp[u], dp[v]);
    maxdown[u].push(maxdown[v].a + 1);
  }
  dp[u] = max(dp[u], maxdown[u].a);
  dp[u] = max(dp[u], maxdown[u].a + maxdown[u].b);

  pre[u].resize(adj[u].size());
  prep[u].resize(adj[u].size());
  for(int i=0; i<adj[u].size(); i++) {
    if(i == 0) {
      pre[u][i].push(maxdown[adj[u][i]].a + 1);
      prep[u][i] = dp[adj[u][i]];
    } else {
      pre[u][i] = pre[u][i-1];
      pre[u][i].push(maxdown[adj[u][i]].a + 1);
      prep[u][i] = max(prep[u][i-1], dp[adj[u][i]]);
    }
  }

  suf[u].resize(adj[u].size());
  sufp[u].resize(adj[u].size());
  for(int i=(int)adj[u].size()-1; i>=0; i--) {
    if(i+1 == adj[u].size()) {
      suf[u][i].push(maxdown[adj[u][i]].a + 1);
      sufp[u][i] = dp[adj[u][i]];
    } else {
      suf[u][i] = suf[u][i+1];
      suf[u][i].push(maxdown[adj[u][i]].a + 1);
      sufp[u][i] = max(sufp[u][i+1], dp[adj[u][i]]);
    }
  }
}

void solve_up(int u, int i) {
  int p = par[u];
  if(p != 1) {
    up[u] = max(up[u], up[p]);
    maxup[u].push(maxup[p].a + 1);
  }
  if(i > 0) {
    maxup[u].push(pre[p][i-1].a);
    maxup[u].push(pre[p][i-1].b);
    up[u] = max(up[u], prep[p][i-1]);
  }
  if(i+1 < adj[p].size()) {
    maxup[u].push(suf[p][i+1].a);
    maxup[u].push(suf[p][i+1].b);
    up[u] = max(up[u], sufp[p][i+1]);
  }
  up[u] = max(up[u], maxup[u].a);
  up[u] = max(up[u], maxup[u].a + maxup[u].b);

  for(int j=0; j<adj[u].size(); j++) {
    solve_up(adj[u][j], j);
  }
}

int rev[N];

vector<int> bfs(int s) {
  memset(rev, -1, sizeof rev);
  queue<int> nxt;
  rev[s] = 0;
  nxt.push(s);

  int last = s;
  while(!nxt.empty()) {
    int u = nxt.front();
    nxt.pop();
    last = u;
    for(int v : adj[u]) {
      if(rev[v] == -1) {
        rev[v] = u;
        nxt.push(v);
      }
    }
  }

  vector<int> out;
  for(int u=last; u; u=rev[u]) {
    out.push_back(u);
  }
  return out;
}

int find_center(int r, int diam) {
  int o = bfs(r).front();
  vector<int> path = bfs(o);
  assert(path.size() == diam + 1);
  return path[path.size()/2];
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

  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  build(1, 0);
  solve_down(1);
  for(int i=0; i<adj[1].size(); i++) {
    solve_up(adj[1][i], i);
  }

  int ans = INF;
  int r = -1;
  for(int i=2; i<=n; i++) {
    int cur = (dp[i]+1)/2 + (up[i]+1)/2 + 1;
    cur = max(cur, max(dp[i], up[i]));
    if(cur < ans) {
      ans = cur;
      r = i;
    }
  }

  rebuild(1);
  adj[r].erase(find(adj[r].begin(), adj[r].end(), par[r]));
  adj[par[r]].erase(find(adj[par[r]].begin(), adj[par[r]].end(), r));

  int cr = find_center(r, dp[r]);
  int cp = find_center(par[r], up[r]);
  cout << ans << nl;
  cout << r << " " << par[r] << nl;
  cout << cr << " " << cp << nl;

  return 0;
}
