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

  int n;
  cin >> n;
  vector<int> cost(n), lens(n);
  for(int i=0; i<n; i++) {
    cin >> cost[i];
  }
  for(int i=1; i<n; i++) {
    cin >> lens[i];
  }

  vector<ll> full(n);
  for(int i=1; i<n; i++) {
    full[i] = full[i-1] + (ll) cost[i-1] * lens[i];
  }
  partial_sum(lens.begin(), lens.end(), lens.begin());

  int t, m;
  cin >> t >> m;
  vector<int> a(m+2), b(m+2);
  a[m+1] = t + 1;

  function<ll(int,int)> get_cost = [&](int l, int r) {
    int days = a[r] - b[l] - 1;
    int i = prev(upper_bound(lens.begin(), lens.end(), days)) - lens.begin();
    return full[i] + (ll) cost[i] * (days - lens[i]);
  };

  vector<ll> dp(m+1, INFLL);
  dp[0] = 0;
  for(int i=1; i<=m; i++) {
    cin >> a[i] >> b[i];
    for(int j=0; j<i; j++) {
      dp[i] = min(dp[i], dp[j] + get_cost(j, i));
    }
  }

  ll ans = INFLL;
  for(int i=0; i<=m; i++) {
    ans = min(ans, dp[i] + get_cost(i, m+1));
  }
  cout << ans << nl;

  return 0;
}
