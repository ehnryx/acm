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
  int a, b;
  cin >> a >> b;
  a -= 1;
  b -= 1;

  int ans = 0;

  for(int i=0; i<a; i++) {
    ll jj = (ll)a*a - (ll)i*i;
    ll j = sqrt(jj);
    if(j*j != jj) {
      continue;
    }

    ll c = (ll)i * b/a;
    ll d = (ll)j * b/a;
    if(c*a != (ll)i*b or d*a != (ll)j*b) {
      continue;
    }

    ans++;
  }

  if(a != b) {
    ans *= 2;
  }

  cout << ans << nl;
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
