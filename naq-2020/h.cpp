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

  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  int len = s.size();
  transform(s.begin(), s.end(), s.begin(), [](char c) { return c - '0' + 1; });

  swap(n, m);
  vector g(n, vector<char>(m));
  for(int i=n-1; i>=0; i--) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
      g[i][j] -= '0';
    }
  }

  vector dist(n, vector(m, vector<int>(len+1, INF)));
  dist[0][0][0] = g[0][0];
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      for(int k=0; k<=len; k++) {
        if(i > 0) {
          dist[i][j][k] = min(dist[i][j][k], g[i][j] + dist[i-1][j][k]);
        }
        if(j > 0) {
          dist[i][j][k] = min(dist[i][j][k], g[i][j] + dist[i][j-1][k]);
        }
        if(k > 0 && i >= s[k-1]) {
          dist[i][j][k] = min(dist[i][j][k], g[i][j] + dist[i-s[k-1]][j][k-1]);
        }
        if(k > 0 && j >= s[k-1]) {
          dist[i][j][k] = min(dist[i][j][k], g[i][j] + dist[i][j-s[k-1]][k-1]);
        }
      }
    }
  }
  cout << *min_element(dist[n-1][m-1].begin(), dist[n-1][m-1].end()) << nl;

  return 0;
}
