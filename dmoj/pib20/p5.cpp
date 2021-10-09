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
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3 + 1;
int d[N][N], p[N][N], a[N][N], m[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  int h = (n-1) / 2;

  for(int i=0; i<n; i++) {
    for(int j=1; j<n; j++) {
      cin >> d[i][j];
      a[j][i] = a[j-1][i] + d[i][j];
    }
  }

  for(int i=0; i<n; i++) {
    sort(a[i], a[i]+n);
    m[i] = a[i][h];
  }
  sort(m, m+n);
  int v = -m[h];

  cout << "YES" << nl;
  for(int i=0; i<n; i++) {
    cout << v << " ";
  }
  cout << nl;

  return 0;
}
