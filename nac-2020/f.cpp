//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int v, c;
  bool operator < (const Edge& o) const {
    return c > o.c;
  }
};

const int N = 50;
const int M = N*N + 2;
const int S = M-1;
const int T = M-2;
int g[N][N];
vector<Edge> adj[M];
int dist[M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(g[i][j] == 1) {
        adj[S].push_back({i*n+j, 0});
      }
      if(g[i][j] == k) {
        adj[i*n+j].push_back({T, 0});
      }
      for(int ii=0; ii<n; ii++) {
        for(int jj=0; jj<n; jj++) {
          if(g[ii][jj] - g[i][j] == 1) {
            adj[i*n+j].push_back({ii*n+jj, abs(i-ii)+abs(j-jj)});
          }
        }
      }
    }
  }

  memset(dist, -1, sizeof dist);
  priority_queue<Edge> dijk;
  dijk.push({S,0});
  while(!dijk.empty()) {
    auto [u, d] = dijk.top();
    dijk.pop();
    if(dist[u] == -1) {
      dist[u] = d;
      if(u == T) {
        cout << d << nl;
        return 0;
      }
      for(auto [v, e] : adj[u]) {
        if(dist[v] == -1) {
          dijk.push({v, d+e});
        }
      }
    }
  }
  cout << -1 << nl;

  return 0;
}
