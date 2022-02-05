#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Edge {
  int v, d;
  //* c++20 where??
  Edge() = default;
  Edge(int _v, int _d): v(_v), d(_d) {}
  //*/
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  vector<vector<Edge>> adj(n);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  int night, day;

  {
    vector<int> dist(n, -1);
    priority_queue<Edge> bfs;
    bfs.emplace(0, 0);
    while(!empty(bfs)) {
      auto [u, d] = bfs.top();
      bfs.pop();
      if(dist[u] != -1) continue;
      dist[u] = d;
      for(auto [v, c] : adj[u]) {
        if(dist[v] == -1) {
          bfs.emplace(v, d + c);
        }
      }
    }
    night = dist[n-1] + ((dist[n-1] - 1) / 12 * 12);
  }

  {
    vector<int> dist(n, -1);
    priority_queue<Edge> bfs;
    bfs.emplace(0, 0);
    while(!empty(bfs)) {
      auto [u, d] = bfs.top();
      bfs.pop();
      if(dist[u] != -1) continue;
      dist[u] = d;
      for(auto [v, c] : adj[u]) {
        if(dist[v] == -1) {
          int nd = d + c;
          if (d % 24 + c > 12) {
            nd = d / 24 * 24 + 24 + c;
          }
          bfs.emplace(v, nd);
        }
      }
    }
    day = dist[n-1];
  }

  cerr << "day, night: " << day << ", " << night << nl;

  cout << day - night << nl;

  return 0;
}
