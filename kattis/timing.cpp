//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef /*long*/ double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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

  int T;
  cin >> T;
  while(T--) {
    int n, m, t;
    cin >> n >> m >> t;
    vector<ld> val(n);
    for(int i=0; i<n; i++) {
      cin >> val[i];
    }
    vector adj(n, vector<ld>(n));
    vector<vector<int>> graph(n);
    for(int i=0; i<m; i++) {
      int a, b; ld c;
      cin >> a >> b >> c;
      adj[a][b] = c;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    for(int i=0; i<n; i++) {
      adj[i][i] = 1 - accumulate(adj[i].begin(), adj[i].end(), (ld) 0);
      graph[i].push_back(i);
    }

    for(int tt=0; tt<t; tt++) {
      vector<ld> nv(n);
      for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
          nv[j] += adj[i][j] * val[i];
        }
      }
      val = move(nv);
    }

    ld ans = 1e19;
    for(int i=0; i<n; i++) {
      ld cur = 0;
      for(int j : graph[i]) {
        cur += val[j];
      }
      ans = min(ans, cur);
    }
    cout << ans << nl;
  }

  return 0;
}
