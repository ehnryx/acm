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

  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  vector<pair<int, int>> b(m);
  for(int i=0; i<m; i++) {
    cin >> b[i].second >> b[i].first;
  }

  sort(begin(a), end(a), greater<>());
  sort(begin(b), end(b), greater<>());

  ll ans = 0;
  for(int i=0, j=0; i<m; i++) {
    while(j<n && b[i].second) {
      ans += (ll)b[i].first * a[j];
      b[i].second--;
      j++;
    }
  }
  cout << ans << nl;

  return 0;
}
