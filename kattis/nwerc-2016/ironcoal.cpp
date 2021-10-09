//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 1e8;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<int> get_dists(const vector<vector<int>>& g, const vector<int>& s) {
  vector<int> d(g.size(), -1);
  queue<int> bfs;
  for(int it : s) {
    d[it] = 0;
    bfs.push(it);
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : g[u]) {
      if(d[v] == -1) {
        d[v] = d[u] + 1;
        bfs.push(v);
      }
    }
  }
  transform(d.begin(), d.end(), d.begin(), [](int v) {
    return v == -1 ? INF : v;
  });
  return d;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m, k;
  cin >> n >> m >> k;
  vector<int> iron(m), coal(k);
  for(int i=0; i<m; i++) {
    cin >> iron[i];
  }
  for(int i=0; i<k; i++) {
    cin >> coal[i];
  }

  vector<vector<int>> adj(n+1);
  vector<vector<int>> rev(n+1);
  for(int i=1; i<=n; i++) {
    int len;
    cin >> len;
    adj[i].resize(len);
    for(int j=0; j<len; j++) {
      cin >> adj[i][j];
      rev[adj[i][j]].push_back(i);
    }
  }

  vector<int> to_iron = get_dists(rev, iron);
  vector<int> to_coal = get_dists(rev, coal);
  vector<int> from_start = get_dists(adj, {1});
  int ans = INF;
  for(int i=1; i<=n; i++) {
    ans = min(ans, to_iron[i] + to_coal[i] + from_start[i]);
  }
  if(ans == INF) {
    cout << "impossible" << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
