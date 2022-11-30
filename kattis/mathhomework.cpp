#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
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

  auto [a, b, c, t] = cin.getv<int, int, int, int>();
  vector<tuple<int, int, int>> out;
  for(int i=0; i*a<=t; i++) {
    for(int j=0; i*a+j*b<=t; j++) {
      int need = t - (i*a + j*b);
      if (need % c == 0) {
        out.emplace_back(i, j, need / c);
      }
    }
  }
  if (out.empty()) {
    cout << "impossible" << nl;
  } else {
    cout << container_view(out, "\n") << nl;
  }

  return 0;
}
