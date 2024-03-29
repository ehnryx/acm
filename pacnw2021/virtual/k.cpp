#include <bits/stdc++.h>
using namespace std;

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

  int n, k;
  cin >> n >> k;

  vector<int> a(1<<n);
  for(int i=0; i<1<<n; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a), greater<>());

  int ans = 0;
  for(int i=0; i<n; i++) {
    for(int j=0, r=1<<i; j<1<<i; j++) {
      if (a[j] - a[r] <= k) {
        ans++;
        r++;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
