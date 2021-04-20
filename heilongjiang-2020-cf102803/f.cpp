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

  int T;
  cin >> T;
  while(T--) {
    vector<int> x(1), y(1);
    cin >> x[0] >> y[0];
    int n;
    cin >> n;
    x.resize(n+1);
    y.resize(n+1);
    for(int i=1; i<=n; i++) {
      cin >> x[i] >> y[i];
    }

    vector<vector<int>> adj(2*(n+1)); // 0 = they move, 1 = we move
    for(int i=0; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        if(i == j) continue;
        if(i > 0 && y[j] < y[i]) continue;
        // can we catch j from i
        for(int t=0; t<2; t++) {
          int dx = abs(x[i] - x[j]);
          int dy = y[j] + t - y[i];
          if(dx < dy) {
            adj[2*i + t].push_back(2*j + 1);
            //cerr << "add edge " << i << " " << t << " -> " << j << " 1" << nl;
          } else if(dx == dy) {
            adj[2*i + t].push_back(2*j + 0);
            //cerr << "add edge " << i << " " << t << " -> " << j << " 0" << nl;
          }
        }
      }
    }

    vector<int> deg(2*(n+1));
    int start = 0 + 1; // we start
    queue<int> bfs;
    bfs.push(start);
    while(!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      for(int v : adj[u]) {
        if(deg[v] == 0) {
          bfs.push(v);
        }
        deg[v]++;
      }
    }

    vector<int> ans(2*(n+1), -INF);
    ans[start] = 0;
    bfs.push(start);
    while(!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      for(int v : adj[u]) {
        ans[v] = max(ans[v], ans[u] + 1);
        //cerr << "upd " << v << " <- " << u << " : " << ans[v] << nl;
        if(--deg[v] == 0) {
          bfs.push(v);
        }
      }
    }
    cout << *max_element(begin(ans), end(ans)) << nl;
  }

  return 0;
}
