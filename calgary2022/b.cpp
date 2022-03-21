#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

pair<ld, ld> solve(int n, int k, int cur) {
  if(k == 0) return pair((ld)0, (ld)0);
  ld c = 1;
  ld m = 0;
  int mid = cur | 1 << (k-1);
  if (mid >= n) {
    m += (ld)1/2;
  } else {
    auto [rc, rm] = solve(n, k-1, mid);
    c += rc/2;
    m += rm/2;
  }
  if (mid <= n) {
    c += (ld)(k-1)/2;
  } else {
    auto [lc, lm] = solve(n, k-1, cur);
    c += lc/2;
    m += lm/2;
  }
  return pair(c, m);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  int k = ceil(log2(n));
  auto [c, m] = solve(n, k, 0);
  cout << c / (1 - m) << nl;

  return 0;
}
