#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"
//%:include "number/fraction.h"

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
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int w, vk, n;
  cin >> w >> vk >> n;
  auto xy = cin.read<pair<int, int>>(n);

  function<bool(int)> solve = [=](int v) {
    int at = xy[0].second;
    ll l = xy[0].first * (ll)v;
    ll r = l + w * (ll)v;
    for(int i=1; i<n; i++) {
      int dy = xy[i].second - at;
      ll dx = (ll)vk * dy;
      l = max(l - dx, xy[i].first * (ll)v);
      r = min(r + dx, (xy[i].first + w) * (ll)v);
      if(r < l) return false;
      at = xy[i].second;
    }
    return true;
  };

  int m;
  cin >> m;
  auto skis = cin.read<int>(m);
  skis.push_back(0);
  sort(begin(skis), end(skis));

  int l = 0;
  int r = m;
  while(l < r) {
    int v = (l + r + 1) / 2;
    if(solve(skis[v])) {
      l = v;
    } else {
      r = v - 1;
    }
  }

  if(r) {
    cout << skis[r] << nl;
  } else {
    cout << "IMPOSSIBLE" << nl;
  }

  return 0;
}
