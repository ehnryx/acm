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
random_device _rd; mt19937 rng(_rd());



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
  vector<vector<int>> adj(3*n + 1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[abs(a)].push_back(b + n);
    if(a < 0) {
      adj[abs(a)].push_back(b);
      adj[abs(a) + n].push_back(b + n);
    }
  }
  for(int i=1; i<=n; i++) {
    if(!adj[i].empty() && *min_element(begin(adj[i]), end(adj[i])) > n) {
      adj[i].push_back(i + 2*n);
    }
  }

  vector<bool> vis(3*n + 1);
  queue<int> bfs;
  bfs.push(1);
  vis[1] = true;
  vector<int> res;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    if(adj[u].empty()) {
      res.push_back((u-1) % n + 1);
    }
    for(int v : adj[u]) {
      if(!vis[v]) {
        bfs.push(v);
        vis[v] = true;
      }
    }
  }

  sort(begin(res), end(res));
  cout << unique(begin(res), end(res)) - begin(res) << nl;

  return 0;
}
