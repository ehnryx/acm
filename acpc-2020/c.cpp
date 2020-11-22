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

  int n, m, s;
  cin >> m >> n >> s;
  vector g(n, vector<char>(m, '_'));
  for(int i=0; i<s; i++) {
    int a, b, c, r;
    cin >> c >> r >> b >> a;
    for(int j=0; j<r; j++) {
      for(int k=0; k<c; k++) {
        if(a+j < n && b+k < m) {
          g[a+j][b+k] = i + 'a';
        }
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cout << g[i][j];
    }
    cout << nl;
  }

  return 0;
}
