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
  vector<ll> orig(3);
  for(int i=0; i<3; i++) {
    cin >> orig[i];
  }

  const ll ub = 5 * (ll)sqrt(orig[0] + orig[1] + orig[2]);
  cerr << "want R <= " << ub << nl;

  uniform_int_distribution<int> d(0, 2);

  vector<tuple<ll, ll, ll>> ans;
  for(int tt=1; clock() < 0.9*CLOCKS_PER_SEC; tt++) {
    cerr << tt << " iterations" << nl;
    ans.clear();
    auto v = orig;
    while(size(ans) < ub-1 &&
        !(__builtin_popcount(v[0] + v[1]) == 1 ||
          __builtin_popcount(v[1] + v[2]) == 1 ||
          __builtin_popcount(v[2] + v[0]) == 1)) {
      int i = d(rng);
      int j = (i+1 == 3 ? 0 : i+1);
      if(v[i] < v[j]) {
        v[j] -= v[i];
        v[i] += v[i];
      } else {
        v[i] -= v[j];
        v[j] += v[j];
      }
      ans.emplace_back(v[0], v[1], v[2]);
    }
    if(__builtin_popcount(v[0] + v[1]) == 1) {
    } else if(__builtin_popcount(v[1] + v[2]) == 1) {
    } else if(__builtin_popcount(v[2] + v[0]) == 1) {
    } else {
      continue;
    }

    cout << size(ans) << nl;
    for(auto [a, b, c] : ans) {
      cout << a << " " << b << " " << c << nl;
    }
    return;
  }

  assert(false);
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
