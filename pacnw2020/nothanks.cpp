#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a));

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0 || a[i] != a[i-1] + 1) {
      ans += a[i];
    }
  }
  cout << ans << nl;

  return 0;
}
