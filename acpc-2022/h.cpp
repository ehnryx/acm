#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  int m = 2*n - 1;
  vector<char> a(m);
  for(int i=0; i<m; i++) {
    cin >> a[i];
  }

  static constexpr ll inf = numeric_limits<ll>::max();
  static constexpr auto bad = pair(-inf, inf);
  static constexpr auto todo = pair(inf, inf);

  vector dp(m+1, vector(m+1, todo));

  // return hi, lo
  auto solve = [&](auto&& self, int l, int r) {
    if(dp[l][r] != todo) {
      return dp[l][r];
    }

    if(r-l == 0) {
      return pair(0ll, 0ll);
    }
    if(not isdigit(a[r-1])) {
      return bad;
    }
    if(r-l == 1) {
      ll v = a[l] - '0';
      return pair(v, v);
    }

    ll hi = -inf;
    ll lo = inf;
    for(int i=l; i<r; i++) {
      auto left = self(self, l, i);
      if(left == bad) continue;
      // multiplication
      if(i != l) {
        if(auto right = self(self, i, r); right != bad) {
          //cerr << "split at " << i << " for " << l << " " << r << " GET* " << left << " : " << right << nl;
          auto all = {
            left.first * right.first,
            left.first * right.second,
            left.second * right.first,
            left.second * right.second,
          };
          hi = max(hi, max(all));
          lo = min(lo, min(all));
        }
      }
      // addition/subtraction
      if(not isdigit(a[i])) {
        if(auto right = self(self, i+1, r); right != bad) {
          //cerr << "split at " << i << " for " << l << " " << r << " GET+- " << left << " : " << right << nl;
          int sgn = (a[i] == '+' ? 1 : -1);
          auto all = {
            left.first + sgn * right.first,
            left.first + sgn * right.second,
            left.second + sgn * right.first,
            left.second + sgn * right.second,
          };
          hi = max(hi, max(all));
          lo = min(lo, min(all));
        }
      }
    }

    //cerr << "DO " << l << " " << r << " -> " << hi << " " << lo << nl;

    return dp[l][r] = pair(hi, lo);
  };

  cout << solve(solve, 0, m).first << nl;
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
