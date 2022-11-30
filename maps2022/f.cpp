#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


using pt = complex<ld>;

ld cross(pt a, pt b) {
  return imag(conj(a) * b);
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, d, g;
  cin >> n >> d >> g;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }

  int base = 0;
  for(int i=1; i<n; i++) {
    if(imag(p[i]) < imag(p[base]) || (imag(p[i]) == imag(p[base]) && real(p[i]) < real(p[base]))) {
      base = i;
    }
  }
  swap(p[0], p[base]);
  sort(begin(p) + 1, end(p), [O=p[0]](const auto& a, const auto& b) {
      return arg(a - O) < arg(b - O); });

  ld area = 0;
  ld perim = 0;
  for(int i=n-1, j=0; j<n; i=j++) {
    area += cross(p[i], p[j]);
    perim += abs(p[i] - p[j]);
  }
  ld r = d * g;
  cout << abs(area) / 2 + perim * r + r*r * M_PIl << nl;
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
