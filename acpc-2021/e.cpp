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

  int n;
  cin >> n;
  map<int, int> cnt;
  for(int i=0; i<n; i++) {
    int a;
    cin >> a;
    cnt[a]++;
  }

  ll ans = 0;
  for(auto [v, c] : cnt) {
    ans += ((c + v) / (v+1)) * (v+1);
  }
  cout << ans << nl;

  return 0;
}
