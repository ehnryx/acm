//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "river"

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
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  ll dp[17];
  dp[1] = 2;
  dp[2] = 4;
  dp[3] = 4;
  dp[4] = 12;
  dp[5] = 16;
  dp[6] = 56;
  dp[7] = 84;
  dp[8] = 324;
  dp[9] = 524;
  dp[10] = 2152;
  dp[11] = 3656;
  dp[12] = 15704;
  dp[13] = 27640;
  dp[14] = 122776;
  dp[15] = 221908;
  dp[16] = 1011756;

  int n;
  cin >> n;
  cout << dp[n] << nl;

  return 0;
}
