//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "cactus"

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

const int N = 1e5 + 1;
vector<pair<char,vector<int>>> ans;
unordered_set<int> done[N];
vector<int> adj[N];
vector<int> tre[N], cyc[N];
vector<int> cycle[N];
int par[N];
bool vis[N];

int cid = 0;
int build(int u, int p) {
  if(vis[u]) {
    done[u].insert(p);
    cycle[cid].push_back(u);
    for(int v=p; v!=u; v=par[v]) {
      cycle[cid].push_back(v);
    }
    cyc[u].push_back(cid++);
    return u;
  }
  vis[u] = true;
  par[u] = p;
  if(p) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
  int wait = -1;
  for(int v : adj[u]) {
    if(done[u].count(v)) continue;
    int to = build(v, u);
    if(to == -1) {
      tre[u].push_back(v);
    } else if(to != u) {
      wait = to;
    }
  }
  return wait;
}

void solve(int);
void solve_cyc(int);

void solve(int u) {
  for(int v : tre[u]) {
    solve(v);
    ans.emplace_back('j', vector{u, v});
  }
  ans.emplace_back('c', vector{u, 1, 2});
  ans.emplace_back('r', vector{u, 2, 3});
  for(int c : cyc[u]) {
    solve_cyc(c);
  }
  ans.emplace_back('r', vector{u, 1, 2});
}

void solve_cyc(int c) {
  int root = cycle[c][0];
  int len = cycle[c].size();
  for(int i=1; i<len; i++) {
    solve(cycle[c][i]);
  }
  for(int i=1; i<len; i++) {
    if(i == 1) {
      ans.emplace_back('j', vector{root, cycle[c][i]});
      ans.emplace_back('c', vector{root, 1, 2});
    } else {
      ans.emplace_back('r', vector{root, 4, 3});
      ans.emplace_back('r', vector{root, 2, 4});
      ans.emplace_back('j', vector{root, cycle[c][i]});
      ans.emplace_back('c', vector{root, 4, 2});
    }
  }
  ans.emplace_back('c', vector{root, 1, 2});
  ans.emplace_back('r', vector{root, 2, 3});
  ans.emplace_back('r', vector{root, 4, 3});
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

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int k;
    cin >> k;
    vector<int> path(k);
    for(int j=0; j<k; j++) {
      cin >> path[j];
      if(j > 0) {
        adj[path[j-1]].push_back(path[j]);
        adj[path[j]].push_back(path[j-1]);
      }
    }
  }
  build(1, 0);
  solve(1);

  cout << ans.size() << nl;
  for(auto [c, v] : ans) {
    cout << c;
    for(int it : v) {
      cout << " " << it;
    }
    cout << nl;
  }

  return 0;
}
