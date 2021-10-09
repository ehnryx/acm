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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int k;
  cin >> k;
  const int M = (1<<18) - 1;
  vector<vector<int>> ans = {
    { M, M>>1, M>>1, 0 },
    { 1<<17 | ((M>>1) - k), 0, M>>1, 0 },
    { M, M, M, M>>1 },
  };
  cout << 3 << " " << 4 << nl;
  for(int i=0; i<3; i++) {
    for(int j=0; j<4; j++) {
      cout << ans[i][j] << " ";
    }
    cout << nl;
  }

  return 0;
}
