#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

// calculate points
bool solve(vector<int> v) {
  static constexpr int n = 14;
  assert(size(v) == n);
  sort(begin(v), end(v));
  vector<char> dp(1<<n);
  for(int i=1; i<n; i++) {
    if(v[i] == v[i-1]) {
      dp[1<<i | 1<<(i-1)] = true;
    }
  }
  for(int bm=0; bm<1<<n; bm++) {
    if((__builtin_popcount(bm) - 2) % 3) continue;
    for(int i=0; i<n; i++) {
      if(!(bm & 1<<i)) continue;
      for(int j=0; j<i; j++) {
        if(!(bm & 1<<j)) continue;
        for(int k=0; k<j; k++) {
          if(!(bm & 1<<k)) continue;
          if((v[i] == v[j] && v[j] == v[k]) ||
              (v[i] == v[j] + 1 && v[j] == v[k] + 1)) {
            dp[bm] |= dp[bm ^ 1<<i ^ 1<<j ^ 1<<k];
          }
        }
      }
    }
  }
  return dp[(1<<n) - 1];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int x;
  cin >> x;
  auto v = cin.read<int>(14);
  sort(begin(v), end(v));

  vector<int> all;
  for(int i=1; i<=9; i++) {
    for(int j=0; j<4; j++) {
      all.push_back(i);
    }
  }

  vector<int> pool;
  set_difference(begin(all), end(all), begin(v), end(v), back_inserter(pool));

  map<vector<int>, int> memo;

  vector<int> sum(14);
  for(int add : pool) {
    v.push_back(add);
    for(int i=0; i<14; i++) {
      auto w = v;
      w.erase(begin(w) + i);
      sort(begin(w), end(w));
      if(!memo.count(w)) {
        memo[w] = solve(w) ? 1 + count(begin(w), end(w), x) : 0;
      }
      sum[i] += memo[w];
    }
    v.pop_back();
  }

  cout << (ld)*max_element(begin(sum), end(sum)) / size(pool) << nl;

  return 0;
}
