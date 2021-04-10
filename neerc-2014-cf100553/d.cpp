#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef double ld;
constexpr char nl = '\n';

#define FNAME "damage"

const int M = 8e6;

const ld PI = acos((ld)-1);

template <class F>
ld quad(ld a, ld b, const F& f, const int n = M) {
  ld h = (b-a)/2 / n, v = f(a) + f(b);
  for(int i=1; i<n*2; i++) v += f(a + i*h) * (i&1 ? 4 : 2);
  return v * h / 3;
}

ld angle(ld x) {
  return max((ld)-1, min((ld)1, x));
}

ld cap_area(ld h, ld r) {
  assert(h <= r);
  ld c = r - h;
  ld q = acos(angle(c / r));
  return r*r * (q - sin(2*q)/2);
}

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);
  cout << fixed << setprecision(9);

  ld d, l, r, t, h;
  cin >> d >> l >> r >> t >> h;
  ld c = sqrt(max((ld)0, r*r - d*d/4));

  ld ans = -1;

  if(t == 0) {
    ans = quad(-d/2, -d/2 + h, [=](ld x) -> ld {
      ld ry = sqrt(max((ld)0, d*d/4 - x*x));
      ld e = sqrt(max((ld)0, r*r - x*x)) - c;
      return 2 * cap_area(e, c + e) + 2*ry * l;
    });
  }

  else {
    ld phi = acos(angle(t / l));
    ld m = tan(phi);
    ld h1 = d * sqrt(max((ld)0, l*l - t*t)) / (2*l);
    ld b = (h - h1) * l / t;
    ans = quad(-d/2, d/2, [=](ld x) -> ld {
      ld ry = sqrt(max((ld)0, d*d/4 - x*x));
      ld ub = m*x + b;
      ld e = sqrt(max((ld)0, r*r - x*x)) - c;
      if(ub < -e) {
        return 0;
      } else if(ub < 0) {
        return cap_area(ub + e, c + e);
      } else if(ub < l) {
        return cap_area(e, c + e) + 2*ry * ub;
      } else {
        ld upper = max((ld)0, c + e - (ub - (l - c)));
        return 2 * cap_area(e, c + e) + 2*ry * l - cap_area(upper, c + e);
      }
    });
  }

  assert(ans == ans);
  //assert(ans >= 0);

  ans = ans / 1e6L + 0.005; // ???
  cout << ans << nl;

  return 0;
}
