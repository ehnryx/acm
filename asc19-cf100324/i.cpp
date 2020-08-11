//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "princess"

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

const int N = 2020;
ld logfact[N];
ld logncr(int n, int r) {
  return logfact[n] - logfact[r] - logfact[n-r];
}

ld solve(int n, int m) {
  ld ans = 0;
  for(int i=1; i<n; i++) {
    if(n-i > n-m) continue;
    ld logp = log(m) + logncr(n-m, n-i) + logfact[n-i-1] + logfact[i-1] - logfact[n];
    ans += expl(logp);
  }
  return ans;
}

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

  logfact[0] = 0;
  for(int i=1; i<N; i++) {
    logfact[i] = logfact[i-1] + logl(i);
  }

  int n;
  cin >> n;
  ld ans = (ld)1/n;
  for(int reject=1; reject<n; reject++) {
    ans = max(ans, solve(n, reject));
  }
  cout << ans << nl;

  return 0;
}
