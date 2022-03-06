#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ld cp(const pt& a, const pt& b) { return imag(conj(a) * b); }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }

  ld total = 0;
  for(int i=0, j=n-1; i<n; j=i++) {
    total += cp(v[j], v[i]);
  }
  cerr << "total: " << total << nl;

  ld left = 0;
  ld right = total;
  for(int i=1; i+1<n; i++) {
    ld cur = cp(v[i] - v[0], v[i+1] - v[0]);
    right -= cur;
    if(max(left, right) > total/2) {
      left += cur;
      continue;
    }
    ld ratio = (total/2 - left) / cur;
    pt ans = v[i] * ratio + v[i+1] * (1 - ratio);
    cout << ans.real() << " " << ans.imag() << nl;
    return 0;
  }

  assert(false);

  return 0;
}
