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

auto cross(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    p.emplace_back(a, b);
  }

  static constexpr auto PI = acos(-1.L);

  ld ans = 0;
  for(int r=0; r<2; r++) {
    vector<pt> stk;
    for(int i=0; i<n; i++) {
      while(size(stk) >= 2 and
          (r ? -1 : 1) * cross(stk[size(stk)-1] - p[i], stk[size(stk)-2] - p[i]) <= 0) {
        stk.pop_back();
      }
      if(empty(stk) or imag(p[i]) > imag(stk.back())) {
        stk.push_back(p[i]);
        if(size(stk) >= 2) {
          auto cur = arg(stk[size(stk)-1] - stk[size(stk)-2]);
          ans = max(ans, min(cur, PI-cur));
        }
      }
    }
    reverse(begin(p), end(p));
  }

  cout << ans * 180 / PI << nl;
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
