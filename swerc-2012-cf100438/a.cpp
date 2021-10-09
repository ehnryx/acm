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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 500;
vector<int> adj[N];
int dist[N], par[N];

int solve(int s) {
  memset(par, -1, sizeof par);
  memset(dist, -1, sizeof dist);
  queue<int> bfs;
  bfs.push(s);
  dist[s] = 0;
  int cyc = INF;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(dist[v] == -1) {
        dist[v] = dist[u] + 1;
        par[v] = u;
        bfs.push(v);
      } else if(par[u] != v) {
        cyc = min(cyc, dist[v] + dist[u] + 1);
      }
    }
  }
  return cyc;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int ans = INF;
  for(int i=0; i<n; i++) {
    ans = min(ans, solve(i));
  }
  if(ans < INF) cout << ans << nl;
  else cout << "impossible" << nl;

  return 0;
}
