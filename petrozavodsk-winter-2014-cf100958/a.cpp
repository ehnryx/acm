#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

inline ld sqr(ld x) {
  return x*x;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ld d; cin >> d;
  if (d < 1) {
    cout << fixed << setprecision(10) << d * sqrt(2) << nl;
    return 0;
  }

  ld ans = d * sqrt(2);

  ld y = floor(d);
  ld k = sqrt(sqr(d) - sqr(y));
  if (k < 1) {
    ans = max(ans, y + 1);
  }

  cout << fixed << setprecision(10) << ans << nl;

  return 0;
}
