#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
const ld PI = acos(-1.L);
const ld EPS = 0;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

inline bool on_segment(const pt& a, const pt& b, const pt& p) {
  return abs(cp(b-a, p-a)) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0; }

inline bool on_boundary(const vector<pt>& v, const pt& p) { bool res = 0;
  for (int i = v.size()-1, j = 0; j < v.size(); i=j++)
    res |= on_segment(v[i], v[j], p) | (abs(p-v[i]) < EPS); return res; }

bool pt_in_polygon(const pt& p, const vector<pt>& v) { if (on_boundary(v, p)) return 1;
  ld res = 0; for (int i = v.size() -1 , j = 0; j < v.size(); i = j++)
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p));
  return abs(res) > 1; }


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n; cin >> n;
  vector<pt> a(n);
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    a[i] = pt(x, y);
  }
  int besti; ld best = -1;
  for (int i = 3; i <= 8; i++) {
    ld l = 0, r = 1e8;
    vector<pt> p(i);
    for (int k = 0; k < 200; k++) {
      ld mid = (l+r)/2;
      for (int j = 0; j < i; j++) {
        p[j] = mid*exp(2*PI*j/i*pt(0, 1));
      }
      //cerr << i << " " << mid << nl;
      //for (pt& a : p) cerr << a << " "; cerr << nl;
      bool shit = 0;
      for (int i = 0; i < n; i++) {
        if (pt_in_polygon(a[i], p)) {
          shit = 1;
          break;
        }
      }
      if (shit) {
        r = mid;
      } else l = mid;
    }
    ld l2 = 0, r2 = 1e8;
    for (int k = 0; k < 200; k++) {
      ld mid = (l2+r2)/2;
      for (int j = 0; j < i; j++) {
        p[j] = mid*exp(2*PI*j/i*pt(0, 1));
      }
      bool shit = 0;
      for (int i = 0; i < n; i++) {
        if (!pt_in_polygon(a[i], p)) {
          shit = 1;
          break;
        }
      }
      if (shit) {
        l2 = mid;
      } else r2 = mid;
    }
    //cerr << i << " " << r << " " << r2 << nl;
    //for (pt& a : p) cerr << a << " " << abs(a) << " "; cerr << nl;
    if ((r/r2)*(r/r2) > best) {
      best = (r/r2)*(r/r2);
      besti = i;
    }
  }
  cout << fixed << setprecision(10) << besti << " " << best << nl;

  return 0;
}
