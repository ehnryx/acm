#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"
%:include "math/numerical_integration.h"

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

  int n;
  cin >> n;
  auto circles = cin.read<tuple<int, int, int>>(n);
  function<double(double)> f = [circles](double x) {
    vector<pair<double, int>> ev;
    for(auto [cx, cy, r] : circles) {
      double r2 = r*r;
      double dx2 = (x-cx)*(x-cx);
      if(dx2 < r2) {
        double dy = sqrt(r2 - dx2);
        ev.emplace_back(cy - dy, 1);
        ev.emplace_back(cy + dy, -1);
      }
    }
    sort(begin(ev), end(ev));

    double res = 0;
    int have = 0;
    for(auto [at, t] : ev) {
      if(t == 1 && have == 0) {
        res -= at;
      }
      have += t;
      if(t == -1 && have == 0) {
        res += at;
      }
    }
    return res;
  };

  const int M = 1e3;
  cout << integrate2<double>(f, -20, 20, M) << nl;
  //cout << integrate4<double>(f, -20, 20, M/2) << nl;

  return 0;
}
