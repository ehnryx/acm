#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';

#define FNAME "knockout"

const int N = 1010;
int n, m;
ll a[N], b[N];

ll sgn(ll x) {
  return (x == 0 ? 0 : (x > 0 ? 1 : -1));
}

ll where(int i, ll t) {
  ll A = a[i], B = b[i];
  ll diff = abs(A-B);
  t = t%(2*diff);

  if (t > diff) {
    return B + (t-diff)*sgn(A-B);
  } else {
    return A + (t)*sgn(B-A);
  }
}

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i=1; i<=n; ++i) {
    cin >> a[i] >> b[i];
  }
  for (int i=1; i<=m; ++i) {
    int xi, yi, ti;
    cin >> xi >> yi >> ti;
    int ans = 0;
    for (int j=1; j<=n; ++j) {
      ll w = where(j, ti);
      //cerr << "    " << w << endl;
      if (w >= xi && w <= yi) {
        ++ ans;
      }
    }
    cout << ans << "\n";
  }

  return 0;
}
