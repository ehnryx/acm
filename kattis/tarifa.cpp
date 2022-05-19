#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

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

  int x;
  cin >> x;
  int n;
  cin >> n;
  int have = 0;
  for(int v : cin.read<int>(n)) {
    have += x;
    have -= min(have, v);
  }
  cout << have + x << nl;

  return 0;
}
