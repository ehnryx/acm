#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "math/miller_rabin.h"
%:include "math/pollard_rho.h"

using ll = unsigned long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
//random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  uint64_t n;
  cin >> n;
  if (n <= 1) return;
  vector<uint64_t> ans;
  while(n > 1) {
    uint64_t k = pollard_rho::get_factor<99>(n);
    while (not miller_rabin::is_prime(k)) k = pollard_rho::get_factor<99>(k);
    while (n % k == 0) {
      ans.push_back(k);
      n /= k;
    }
  }
  //auto ans = ubc::prime_factor(n);
  sort(begin(ans), end(ans));
  for(auto v : ans) {
    cout << v << nl;
  }
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
