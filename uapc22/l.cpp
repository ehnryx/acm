#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  vector<ll> a(n);
  for(int i=1; i<n; i++) {
    cin >> a[i];
  }
  vector<ll> sum;
  partial_sum(begin(a), end(a), back_inserter(sum));

  function<bool(ll, ll)> valid = [&](ll lb, ll ub) {
    vector<int> dp(n, 1);
    for(int i=1; i<n; i++) {
      for(int j=0; j<i; j++) {
        if(sum[i] - sum[j] < lb || sum[i] - sum[j] > ub) continue;
        dp[i] = max(dp[i], dp[j] + 1);
        if(dp[i] >= m) {
          return true;
        }
      }
    }
    return false;
  };

  function<ll(ll)> solve = [&](ll maxlen) {
    ll l = 0;
    ll r = maxlen;
    while(l < r) {
      ll mid = (l + r + 1) / 2;
      if(valid(mid, maxlen)) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    return valid(r, maxlen) ? maxlen - r : numeric_limits<ll>::max();
  };

  ll ans = numeric_limits<ll>::max();
  for(int i=1; i<n; i++) {
    for(int j=0; j<i; j++) {
      ans = min(ans, solve(sum[i] - sum[j]));
    }
  }
  assert(ans < numeric_limits<ll>::max());
  cout << ans << nl;

  return 0;
}
