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

unordered_map<ll, int> ans;
int solve(ll n) {
  if (ans.count(n)) return ans[n];
  if (n % 2) return ans[n] = 1 + solve(3 * n + 1);
  else return ans[n] = 1 + solve(n / 2);
};

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

  ans[1] = 1;

  int best = 1;
  for (int i = 1; i < 1'000'000; i++) {
    if (i % 100'000 == 0) cerr << "solve " << i << " , best so far: " << best << nl;
    if (solve(i) > ans[best]) {
      best = i;
    }
  }
  cout << best << nl;
  cout << "length: " << ans[best] << nl;

  cerr << "length of 13: " << ans[13] << nl;

  return 0;
}
