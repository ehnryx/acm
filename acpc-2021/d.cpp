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

  string s;
  cin >> s;
  int n = s.size();
  vector<int> cost(n);
  for(int i=0; i<n; i++) {
    cin >> cost[i];
  }

  // compute all possible bitmasks of all possible lengths,
  // there are less than 64 of these so we can index these
  // and store subsets in an int64
  vector<pair<ll, int>> bms;
  for(int i=0; i<n; i++) {
    for(int j=0; j<=i; j++) {
      ll bm = stoll(s.substr(j, i-j + 1), 0, 2);
      bms.emplace_back(bm, i-j + 1);
    }
  }
  sort(begin(bms), end(bms));
  bms.resize(unique(begin(bms), end(bms)) - begin(bms));

  vector remap(n, vector<int>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<=i; j++) {
      ll bm = stoll(s.substr(j, i-j + 1), 0, 2);
      remap[j][i] = lower_bound(begin(bms), end(bms), pair(bm, i-j + 1)) - begin(bms);
    }
  }

  // pruning this isn't necessary,
  // but 0 and 1 or a full mask would cover the whole thing
  int ub = min(2 * cost[0], cost.back());

  // dp[i][mask] = covered the first i bits with some subset (mask) of bitmasks
  vector<map<ll, int>> dp(n+1);
  dp[0][0] = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<=i; j++) {
      for(auto [have, v] : dp[j]) {
        ll nxt = have | 1LL << remap[j][i];
        int val = v + ((have >> remap[j][i] & 1) ^ 1) * cost[i-j];
        if(val >= ub) continue;
        if(dp[i+1].count(nxt)) {
          dp[i+1][nxt] = min(dp[i+1][nxt], val);
        } else {
          dp[i+1][nxt] = val;
        }
      }
    }
  }

  int ans = ub;
  for(auto [_, v] : dp[n]) {
    ans = min(ans, v);
  }
  cout << ans << nl;

  return 0;
}
