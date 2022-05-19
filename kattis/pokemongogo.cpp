#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "geometry/point.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int solve(const auto& ev, const auto& all, int bm, int at, auto& dp) {
  if(bm == 0) {
    return all[at].dist_Lone(point(0, 0));
  }
  if(dp[bm][at] != -1) return dp[bm][at];

  int res = numeric_limits<int>::max();
  for(int i=0; i<size(ev); i++) {
    if(!(bm & 1<<i)) continue;
    for(int to : ev[i]) {
      res = min(res, all[at].dist_Lone(all[to]) + solve(ev, all, bm ^ 1<<i, to, dp));
    }
  }
  return dp[bm][at] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<vector<int>> ev;
  vector<point<int>> all;
  unordered_map<string, int> remap;
  for(int i=0, rid=0; i<n; i++) {
    int a, b; string s;
    cin >> a >> b >> s;
    all.emplace_back(a, b);
    if(!remap.count(s)) {
      remap[s] = rid++;
      ev.emplace_back();
    }
    ev[remap[s]].push_back(i);
  }
  all.emplace_back(0, 0);
  int m = size(ev);

  vector dp(1 << m, vector<int>(n+1, -1));
  cout << solve(ev, all, (1 << m) - 1, n, dp) << nl;

  return 0;
}
