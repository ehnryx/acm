#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  int n, u, t;
  cin >> n >> u >> t;

  int w[n], v[n];
  int sum = 0;
  int maxv = 0;
  for (int i = 0; i < n; i++) {
    cin >> w[i] >> v[i];
    sum += w[i];
    maxv = max(maxv, v[i]);
  }

  int maxsum = 0;
  for (int i = 0; i < n; i++) {
    if (v[i] == maxv) {
      maxsum += w[i];
    }
  }

  if (t*u < sum) {
    cout << -1 << nl;
  }

  else {
    ld ans[n];
    ld htime = (ld)(sum-maxsum)/u;
    ld dtime = t - htime;
    ld dspeed = (ld)maxsum/dtime;

    ld dist = 0;
    for (int i = 0; i < n; i++) {
      if (maxv == v[i]) {
        ans[i] = dtime * w[i] / maxsum;
        ld s = sqrt(u*u - dspeed*dspeed);
        dist += (s + v[i]) * ans[i];
      } else {
        ans[i] = htime * w[i] / (sum-maxsum);
        dist += v[i] * ans[i];
      }
    }

    cout << sqrt(dist*dist + sum*sum) << nl;
    for (int i = 0; i < n; i++) {
      cout << ans[i] << ' ';
    }
    cout << nl;
  }

  return 0;
}
