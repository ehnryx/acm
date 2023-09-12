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

using pt = complex<ld>;

ld cp(const pt& a, const pt& b) { return imag(conj(a) * b); }

ld area(const vector<pt>& v) {
  ld ans = 0;
  for(int i=(int)size(v)-1, j=0; j<size(v); i=j++) {
    ans += cp(v[i], v[j]);
  }
  return ans / 2;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  for(int n; cin >> n and n; ) {
    vector<pt> p;
    for(int i=0; i<n; i++) {
      int a, b;
      cin >> a >> b;
      p.emplace_back(a, b);
    }
    ld ans = area(p);
    if(ans > 0) {
      cout << "CCW " << ans << nl;
    } else {
      cout << "CW " << -ans << nl;
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(1);
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
