#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  unordered_set<ll> bad;
  for(int i=0; i<m; i++) {
    ll v;
    cin >> v;
    while(v) {
      bad.insert(v);
      v /= 2;
    }
  }

  vector<ll> ans;
  auto solve = [&](auto& self, ll i) -> void {
    if(!bad.count(i)) {
      ans.push_back(i);
      return;
    }
    if(i < 1ll<<n) {
      self(self, 2*i);
      self(self, 2*i+1);
    }
  };
  solve(solve, 1);

  sort(begin(ans), end(ans));
  cout << ans << nl;

  return 0;
}
