#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const ld PI = acos((ld)-1);

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  ld w, h;
  cin >> w >> h;

  int n;
  cin >> n;

  if(n == 0) {
    cout << min(w, h) / 2 << nl;
    return 0;
  }

  vector<pair<pt, ld>> cc;
  for(int i=0; i<n; i++) {
    ld x, y, r;
    cin >> x >> y >> r;
    cc.emplace_back(pt(x, y), r);
  }

  for(int i=0; i<size(cc); i++) {
    bool ok = true;
    for(int j=0; j<size(cc); j++) {
      if(i == j) continue;
      if(cc[i].second + abs(cc[i].first - cc[j].first) <= cc[j].second) {
        ok = false;
        break;
      }
    }
    if(!ok) {
      cc.erase(begin(cc) + i);
      i--;
    }
  }
  n = size(cc);

  ld ans = 0;

  for(int i=0; i<n; i++) {
    const auto [c, radius] = cc[i];

    ld l = 0;
    ld r = min(w, h) / 2;

    for(int bs=0; bs<99; bs++) {
      ld m = (l + r) / 2;

      vector<pair<ld, int>> ev;
      int start = 0;

      function<void(pt, pt)> add_line = [&](const pt& a, const pt& b) {
        ld dist = abs(a.real() == b.real() ? c.real() - a.real() : c.imag() - a.imag());
        ld height = abs(dist - m);
        ld diff2 = (radius+m) * (radius+m) - height * height;
        if(diff2 <= 0) return;
        ld diff = sqrt(diff2);
        ld s, t;
        if(a.real() == b.real()) {
          if(c.real() < a.real()) {
            s = arg(pt(a.real() - m, c.imag() - diff) - c);
            t = arg(pt(a.real() - m, c.imag() + diff) - c);
          } else {
            s = arg(pt(a.real() + m, c.imag() + diff) - c);
            t = arg(pt(a.real() + m, c.imag() - diff) - c);
          }
        } else {
          if(c.imag() < a.imag()) {
            s = arg(pt(c.real() + diff, a.imag() - m) - c);
            t = arg(pt(c.real() - diff, a.imag() - m) - c);
          } else {
            s = arg(pt(c.real() - diff, a.imag() + m) - c);
            t = arg(pt(c.real() + diff, a.imag() + m) - c);
          }
        }
        while(s < 0) s += 2*PI;
        while(s >= 2*PI) s -= 2*PI;
        while(t < 0) t += 2*PI;
        while(t >= 2*PI) t -= 2*PI;
        ev.emplace_back(s, -1);
        ev.emplace_back(t, 1);
        start += (s > t);
      };

      function<void(pt, ld)> add_circle = [&](const pt& o, ld other) {
        ld dist = abs(c - o);
        ld leg = radius + m;
        ld opp = other + m;
        ld cosq = (dist*dist + leg*leg - opp*opp) / (2 * dist * leg);
        if(abs(cosq) >= 1) return;
        ld diff = acos(cosq);
        ld a = arg(o - c);
        ld s = a - diff;
        ld t = a + diff;
        while(s < 0) s += 2*PI;
        while(s >= 2*PI) s -= 2*PI;
        while(t < 0) t += 2*PI;
        while(t >= 2*PI) t -= 2*PI;
        ev.emplace_back(s, -1);
        ev.emplace_back(t, 1);
        start += (s > t);
      };

      // lines
      add_line(pt(0, 0), pt(w, 0));
      add_line(pt(w, 0), pt(w, h));
      add_line(pt(w, h), pt(0, h));
      add_line(pt(0, h), pt(0, 0));

      // circles
      for(int j=0; j<n; j++) {
        if(i == j) continue;
        add_circle(cc[j].first, cc[j].second);
      }

      bool ok = (start == 0);
      sort(begin(ev), end(ev));
      for(auto [_, v] : ev) {
        start -= v;
        ok |= (start == 0);
        assert(start >= 0);
      }
      if(ok) {
        l = m;
      } else {
        r = m;
      }
    }

    ans = max(ans, r);
  }

  cout << ans << nl;

  return 0;
}
