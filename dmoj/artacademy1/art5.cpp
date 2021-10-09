//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e3 + 7;
int x[N], y[N];
int dp[N], ndp[N];

int distance(int i, int j) {
  return abs(x[i]-x[j]) + abs(y[i]-y[j]);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n >> x[0] >> y[0] >> x[1] >> y[1];

  memset(dp, INF, sizeof dp);
  dp[0] = 0;

  for(int i=2; i<n+2; i++) {
    cin >> x[i] >> y[i];
    memset(ndp, INF, sizeof ndp);
    for(int j=0; j<i-1; j++) {
      ndp[j] = min(ndp[j], dp[j] + distance(i, i-1));
      ndp[i-1] = min(ndp[i-1], dp[j] + distance(i, j));
    }
    swap(dp, ndp);
  }

  cout << *min_element(dp, dp+N) << nl;

  return 0;
}
