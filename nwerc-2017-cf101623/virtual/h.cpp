#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n; cin >> n;
  while (n--) {
    ll a[3]; ll d; cin >> a[0] >> a[1] >> a[2] >> d;
    sort(a, a + 3);
    ll best = 0;
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        if (d < i + j) continue;
        ll p = a[0] + i, q = a[1] + j, r = a[2] + (d - i - j);
        best = max(best, p*p + q*q + r*r + 7*min(p, min(q, r)));
      }
    }
    cout << best << nl;
  }

  return 0;
}
