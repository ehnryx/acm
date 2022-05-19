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

bool win(ll a, ll b) {
  if(a > b) swap(a, b);
  if(b % a == 0) return true;
  if(2*a < b) return true;
  return !win(b - a, a);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  ll a, b;
  cin >> a >> b;
  if(win(a, b)) {
    cout << "win" << nl;
  } else {
    cout << "lose" << nl;
  }

  return 0;
}
