#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-9;

ld cp(const pt& a, const pt& b) {
  return imag(conj(a)*b);
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

ld area(const vector<pt>& v) {
  int n = v.size();
  ld res = 0;
  for(int j=n-1, i=0; i<n; j=i++) {
    res += cp(v[j], v[i]);
  }
  return res / 2;
}

ld solve(const vector<pt>& p) {
  const int n = 4;
  ld top = INF;
  ld bot = -INF;
  ld half = (ld)1/2;
  vector<pt> v;
  for(int j=n-1, i=0; i<n; j=i++) {
    if(abs(p[i].real() - p[j].real()) > EPS) {
      pt it = line_inter(pt(half, 0), pt(half, 1), p[i], p[j]);
      if(it.imag() > 0) {
        top = min(top, it.imag());
      } else {
        bot = max(bot, it.imag());
      }
    }
    if(p[i].real() >= half) {
      v.push_back(p[i]);
    }
  }
  v.push_back(pt(half, top));
  v.push_back(pt(half, bot));
  sort(v.begin(), v.end(), [] (const pt& a, const pt& b) {
    return arg(a) < arg(b);
  });
  return abs(area(v)) * 5 / 124;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  const int n = 4;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    ld x, y;
    cin >> x >> y;
    p.push_back(pt(x, y));
  }

  ld ans = 5 * (ld)5*5*4 / 124;
  const vector<int> val = {3, 6, 4, 1};
  for(int i=0; i<n; i++) {
    ans += val[i] * solve(p);
    for(int j=0; j<n; j++) {
      p[j] *= pt(0, -1);
    }
  }
  cout << ans << nl;

  return 0;
}
