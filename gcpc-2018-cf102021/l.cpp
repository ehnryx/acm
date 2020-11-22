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

const int N = 100 + 7;
int s[N][N], a[N][N];

int get(int x, int y) {
  int res = 0;
  for(int i=x-1; i<=x+1; i++) {
    for(int j=y-1; j<=y+1; j++) {
      if(i<0 || j<0) continue;
      res += a[i][j];
    }
  }
  return res;
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

  int n, m;
  cin >> n >> m;
  for(int i=0; i<=n+1; i++) {
    for(int j=0; j<=m+1; j++) {
      cin >> s[i][j];
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      a[i][j] = s[i-1][j-1] - get(i-1, j-1);
      if(a[i][j] > 1) {
        cout << "impossible" << nl;
        return 0;
      }
    }
  }

  for(int i=0; i<=n+1; i++) {
    for(int j=0; j<=m+1; j++) {
      if(get(i, j) != s[i][j]) {
        cout << "impossible" << nl;
        return 0;
      }
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cout << (a[i][j] ? 'X' : '.');
    }
    cout << nl;
  }

  return 0;
}
