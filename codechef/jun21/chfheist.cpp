#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int n, t, a, d;
    cin >> n >> t >> a >> d;
    int periods = n / t;
    ll ans = (ll)n * a;
    ans += (ll)t * d * periods * (periods - 1) / 2;
    ans += (ll)periods * d * (n - t * periods);
    cout << ans << nl;
  }

  return 0;
}