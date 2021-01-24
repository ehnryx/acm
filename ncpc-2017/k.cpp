#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int b, n, e;
  cin >> b >> n >> e;
  int sb, sn, se;
  cin >> sb >> sn >> se;

  int m = (b+n+e)/2;
  vector<int> c(m);
  for(int i=0; i<m; i++) {
    cin >> c[i];
  }
  //sort(c.begin(), c.end());

  int l = 0;
  int r = c.back() * (se + se);
  while(l < r) {
    int mid = (l + r + 1) / 2;

    bool ok = true;
    auto [cb, cn, ce] = make_tuple(b, n, e);
    for(int i=0; i<m; i++) {
      int need = (mid + c[i] - 1) / c[i];

      if(need <= sb + sb && cb >= 2) {
        cb -= 2;
        continue;
      }

      if(need <= sb + sn && cb >= 1 && cn >= 1) {
        cb -= 1;
        cn -= 1;
        continue;
      }

      if(need <= min(sn + sn, sb + se)) {
        if(sn + sn == min(sn + sn, sb + se)) {
          if(cn >= 2) {
            cn -= 2;
            continue;
          }
        } else {
          if(cb >= 1 && ce >= 1) {
            cb -= 1;
            ce -= 1;
            continue;
          }
        }
      }

      if(need <= max(sn + sn, sb + se)) {
        if(sn + sn == max(sn + sn, sb + se)) {
          if(cn >= 2) {
            cn -= 2;
            continue;
          }
        } else {
          if(cb >= 1 && ce >= 1) {
            cb -= 1;
            ce -= 1;
            continue;
          }
        }
      }

      if(need <= sn + se && cn >= 1 && ce >= 1) {
        cn -= 1;
        ce -= 1;
        continue;
      }

      if(need <= se + se && ce >= 2) {
        ce -= 2;
        continue;
      }

      ok = false;
      break;
    }

    if(ok) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }

  cout << r << nl;

  return 0;
}
