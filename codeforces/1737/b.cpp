#pragma GCC optimize("O3")
#pragma target("sse4")

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

%:include "utility/fast_input.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  vector<pair<ll, int>> ev;
  ev.reserve(2 * T + 1);
  for(int i=1; i<=T; i++) {
    ll a, b;
    cin >> a >> b;
    ev.emplace_back(a-1, -i);
    ev.emplace_back(b, i);
  }
  sort(begin(ev), end(ev));

  vector<unsigned> ans(T);
  {
    static constexpr int M = 1e9;
    ev.emplace_back((ll)(M+1) * (M+1), 0);
    unsigned cur = 0;
    ll v = 0;
    for(int x=1, i=0; x<=M; x+=4) {
      const ll vs[] = {
        v + 2*x   - 1 , v + 3ll*x - 1  , v +  4ll*x - 1,
        v + 4ll*x     , v + 5ll*x + 1  , v +  6ll*x + 2,
        v + 6ll*x + 3 , v + 7ll*x + 5  , v +  8ll*x + 7,
        v + 8ll*x + 8 , v + 9ll*x + 11 , v + 10ll*x + 14,
      };
      while (vs[11] > ev[i].first) {
        const int id = ev[i].second;
        const unsigned good = (vs[0] <= ev[i].first) + (vs[1] <= ev[i].first) + (vs[2] <= ev[i].first)
          + (vs[3] <= ev[i].first) + (vs[4] <= ev[i].first) + (vs[5] <= ev[i].first)
          + (vs[6] <= ev[i].first) + (vs[7] <= ev[i].first) + (vs[8] <= ev[i].first)
          + (vs[9] <= ev[i].first) + (vs[10] <= ev[i].first) + (vs[11] <= ev[i].first);
        const int sgn = (id < 0 ? -1 : 1);
        ans[sgn * id - 1] += sgn * (cur + good);
        i++;
      }
      v = vs[9];
      cur += 12;
    }
  }

  for(int i=0; i<T; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
