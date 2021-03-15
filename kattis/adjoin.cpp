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
  vector<vector<int>> adj(n);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<bool> vis(n);
  function<pair<int,int>(int)> run_bfs = [&](int s) {
    queue<tuple<int,int,int>> bfs;
    bfs.emplace(s, -1, 0);
    pair<int,int> res(s, 0);
    while(!bfs.empty()) {
      auto [u, p, d] = bfs.front();
      bfs.pop();
      vis[u] = true;
      res = pair(u, d);
      for(int v : adj[u]) {
        if(v == p) continue;
        bfs.emplace(v, u, d + 1);
      }
    }
    return res;
  };

  function<int(int)> diameter = [&](int s) {
    return run_bfs(run_bfs(s).first).second;
  };

  vector<int> diams;
  for(int i=0; i<n; i++) {
    if(vis[i]) continue;
    diams.push_back(diameter(i));
  }
  sort(diams.begin(), diams.end(), greater<int>());

  function<int(int)> half = [](int v) {
    return (v + 1) / 2;
  };

  int ans = diams[0];
  if(diams.size() > 1) {
    ans = max(ans, half(diams[0]) + half(diams[1]) + 1);
    if(diams.size() > 2) {
      ans = max(ans, half(diams[1]) + half(diams[2]) + 2);
    }
  }
  cout << ans << nl;

  return 0;
}
