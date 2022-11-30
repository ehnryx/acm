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
  ll a, c;
  cin >> a >> c;

  map<int, int> all;
  auto prime_factor = [&](ll n) {
    static constexpr ll M = 1e6 + 1;
    vector<pair<int, int>> pf;
    for(int i=2; i<M; i++) {
      if(n % i == 0) {
        pf.emplace_back(i, 0);
        while(n % i == 0) {
          pf.back().second++;
          n /= i;
        }
        all[i] += pf.back().second;
      }
    }
    assert(n == 1);
    return pf;
  };

  auto pa = prime_factor(a);
  auto pc = prime_factor(c);

  ll res = 1;
  for(auto [_, v] : all) {
    res *= v + 1;
  }
  res = (res + 1) / 2;
  cout << res * 2 << nl;
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
