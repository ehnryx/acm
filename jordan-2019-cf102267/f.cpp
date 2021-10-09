#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const ld PI = acos((ld)-1);

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
  vector<int> x(n), y(n);
  vector<ld> a(n), r(n);
  for(int i=0; i<n; i++) {
    int _a, _r;
    cin >> x[i] >> y[i] >> _a >> _r;
    a[i] = _a * PI/180;
    r[i] = _r * PI/180;
  }

  vector<vector<int>> adj(n);
  vector<int> deg(n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(i == j) continue;
      pt u(x[i], y[i]);
      pt v(x[j], y[j]);
      ld angle = arg(v - u);
      ld diff = abs(a[i] - angle);
      while(diff > PI) diff -= 2*PI;
      if(abs(diff) <= r[i] + EPS) {
        adj[i].push_back(j);
        deg[j]++;
      }
    }
  }

  queue<int> bfs;
  for(int i=0; i<n; i++) {
    if(deg[i] == 0) {
      bfs.push(i);
    }
  }
  vector<int> order;
  while(!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    order.push_back(u);
    for(int v : adj[u]) {
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }

  if(size(order) < n) {
    cout << -1 << nl;
  } else {
    for(int it : order) {
      cout << it + 1 << " ";
    }
    cout << nl;
  }

  return 0;
}
