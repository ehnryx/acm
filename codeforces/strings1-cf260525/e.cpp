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
  string s;
  cin >> s;
  const int n = size(s);

  vector<int> lpals(n), rpals(n);
  for(int i=0; i<n; i++) {
    // odd
    for(int half=0; i-half>=0 and i+half<n; half++) {
      if(s[i-half] != s[i+half]) break;
      rpals[i-half]++;
      lpals[i+half]++;
    }
    // even
    for(int half=0; i-half>=0 and i+1+half<n; half++) {
      if(s[i-half] != s[i+1+half]) break;
      rpals[i-half]++;
      lpals[i+1+half]++;
    }
  }

  ll ans = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      ans += (ll)lpals[j] * rpals[i];
    }
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
