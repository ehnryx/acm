#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "math/fft.h"

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

  auto read = [&]() -> vector<int> {
    int n;
    cin >> n;
    return cin.read<int>(n + 1);
  };

  int T;
  cin >> T;
  while(T--) {
    auto a = read();
    auto b = read();
    auto c = fft::convolve(a, b);
    while (!c.empty() && c.back() == 0) {
      c.pop_back();
    }
    cout << c.size() - 1 << nl;
    cout << c << nl;
  }

  return 0;
}
