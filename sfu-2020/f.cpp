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
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int n, m;
  cin >> n >> m;

  vector<tuple<int,int,vector<int>>> edges;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    vector<int> c(4);
    for(int j=0; j<4; j++) {
      cin >> c[j];
    }
    edges.emplace_back(a, b, c);
    swap(c[1], c[2]);
    edges.emplace_back(b, a, c);
  }

  vector<vector<int>> dist(n, vector<int>(2, INF));
  dist[0][0] = dist[0][1] = 0;
  for(int bf=0; bf<n; bf++) {
    for(const auto& it : edges) {
      int a, b; vector<int> c;
      tie(a, b, c) = it;
      for(int t=0; t<2; t++) {
        int cur = 0;
        for(int j=0; j<2; j++) {
          cur = max(cur, dist[b][j] + c[2*t+j]);
        }
        dist[a][t] = min(dist[a][t], cur);
      }
    }
  }

  cout << max(dist[1][0], dist[1][1]) << nl;
}

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
    solve();
  }

  return 0;
}
