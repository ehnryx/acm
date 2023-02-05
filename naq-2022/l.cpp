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
  int t, s;
  cin >> t >> s;
  ll totaal = 0, goed = 0;
  for(int i=0; i<=s; i++) {
    int l = 0;
    int r = s;
    while(l < r) {
      int m = (l + r + 1) / 2;
      if(min(m, i) * 3 + 2 * abs(m - i) <= 2 * s) {
        l = m;
      } else {
        r = m-1;
      }
    }
    int hi = t - i;
    totaal += r;
    goed += max(0, min(r, hi));
  }
  totaal *= 4;
  goed *= 4;
  totaal += 1;
  goed += 1;

  if(totaal == goed) {
    cout << 1 << nl;
  } else {
    ll g = gcd(totaal, goed);
    cout << goed/g << "/" << totaal/g << nl;
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
