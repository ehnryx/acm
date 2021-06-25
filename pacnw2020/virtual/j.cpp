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

  int n, m;
  cin >> n >> m;
  vector<vector<pair<char,char>>> edges(n);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    for(int j=0; j<m; j++) {
      for(int k=0; k<j; k++) {
        edges[i].emplace_back(s[j], s[k]);
      }
    }
    sort(edges[i].begin(), edges[i].end());
    if(i > 0) {
      vector<pair<char,char>> it;
      set_intersection(edges[i].begin(), edges[i].end(),
          edges[i-1].begin(), edges[i-1].end(), back_inserter(it));
      edges[i] = move(it);
    }
  }

  vector<vector<int>> adj(m);
  vector<int> deg(m);
  for(auto [a, b] : edges.back()) {
    adj[a-'A'].push_back(b-'A');
    deg[b-'A']++;
  }

  queue<int> bfs;
  vector<int> dist(m);
  for(int i=0; i<m; i++) {
    if(deg[i] == 0) {
      bfs.push(i);
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      dist[v] = max(dist[v], dist[u] + 1);
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }
  cout << *max_element(dist.begin(), dist.end()) + 1 << nl;

  return 0;
}
