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
  ll l = 1;
  ll r = 1e12;
  ll t = 0;
  ll at = 0;
  while(l < r) {
    ll m = (l + r) / 2;
    // at + guess = m
    ll guess = m - at;
    t += guess;
    cout << "? " << t << endl;
    ll res;
    cin >> res;
    if(res == at + guess) {
      l = m + 1;
    } else {
      r = m;
    }
    at = res;
  }

  cout << "! " << r << endl;
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
