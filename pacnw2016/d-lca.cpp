#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "utility/nd_array.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  for(int i=0; i<n; i++) {
    cin >> v[i];
  }
  sort(begin(v), end(v));

  vector<ll> fact(n, 1);
  for(int i=1; i<n; i++) {
    fact[i] = fact[i-1] * i % MOD;
  }

  // dp[smaller left][larger left][rank in window][nog niet in window]
  //  -> number of problems this contributes to.
  nd_array<int, 4> dp(n, n, k, 2, -1);

  auto solve = [&](auto&& self, int smaller, int larger, int rank, int in_window) -> int {
    if(rank < 0) return (smaller + larger + k) * fact[smaller + larger] % MOD;
    if(in_window and not smaller and not larger) {
      return k-1 - rank;
    }
    int& ans = dp(smaller, larger, rank, in_window);
    if(ans != -1) return ans;
    ans = 0;
    if(smaller) {
      ans = (ans + (ll)smaller * self(self, smaller - 1, larger, rank, in_window)) % MOD;
    }
    if(larger) {
      int next_rank = in_window ? rank - 1 : max(0, rank - 1);
      ans = (ans + (ll)larger * self(self, smaller, larger - 1, next_rank, in_window)) % MOD;
    }
    if(not in_window) {
      ans = (ans + self(self, smaller, larger, rank - 1, true)) % MOD;
    }
    return ans;
  };

  int ans = 0;
  for(int i=0; i<n; i++) {
    int cnt = solve(solve, i, n-1 - i, k-1, false);
    ans = (ans + (ll)cnt * v[i]) % MOD;
  }
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
