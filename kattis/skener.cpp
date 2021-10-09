//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m, a, b;
  cin >> n >> m >> a >> b;
  char g[n*a][m*b];
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      char c;
      cin >> c;
      for(int ii=0; ii<a; ii++) {
        for(int jj=0; jj<b; jj++) {
          g[i*a+ii][j*b+jj] = c;
        }
      }
    }
  }
  for(int i=0; i<n*a; i++) {
    for(int j=0; j<m*b; j++) {
      cout << g[i][j];
    }
    cout << nl;
  }

  return 0;
}
