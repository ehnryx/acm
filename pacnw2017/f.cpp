#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

int count(int n, const pt& center, const vector<pt>& p) {
  set<ld> dists;
  for (int i = 0; i < n; i++) {
    ld dist = abs(p[i]-center);
    auto it = dists.lower_bound(dist);
    if (it == dists.end() || abs(*(it) - dist) > EPS) {
      if (it == dists.begin() || abs(*(--it) - dist) > EPS) {
        dists.insert(dist);
      }
    }
  }
  return dists.size();
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int x, y;
  int n;
  cin >> n;
  vector<pt> p;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    p.push_back(pt(x,y));
  }

  int ans = INF;
  if (n < 3) {
    ans = 1;
  } else {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        ans = min(ans, count(n, (ld)0.5*(p[i]+p[j]), p));
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        for (int k = 0; k < n; k++) {
          for (int l = 0; l < k; l++) {
            if (cp(p[i]-p[j], p[k]-p[l]) > EPS) {
              pt perp1 = pt(0,1)*(p[i]-p[j]);
              pt perp2 = pt(0,1)*(p[k]-p[l]);
              pt mid1 = (ld)0.5*(p[i]+p[j]);
              pt mid2 = (ld)0.5*(p[k]+p[l]);
              pt center = line_inter(perp1+mid1, mid1, perp2+mid2, mid2);
              ans = min(ans, count(n, center, p));
            }
          }
        }
      }
    }
  }
  cout << ans << nl;

  return 0;
}
