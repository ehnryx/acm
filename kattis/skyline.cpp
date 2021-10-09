#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef double ld;

const char nl = '\n';
const ld EPS = 1e-11;

struct pt {
  ld x, y;
  pt(const ld& a, const ld& b): x(a), y(b) {}
  pt operator + (const pt& o) const { return pt(x+o.x, y+o.y); }
  pt operator - (const pt& o) const { return pt(x-o.x, y-o.y); }
};
pt operator * (const ld& c, const pt& v) {
  return pt(c*v.x, c*v.y);
}

ld cp(const pt& a, const pt& b) { return a.x*b.y - a.y*b.x; }
int sgn(ld x) { return x < -EPS ? -1 : x < EPS ? 0 : 1; }
bool seg_x_seg(const pt& a, const pt& b, const pt& c, const pt& d) {
  int s1 = sgn(cp(a-b, c-b));
  int s2 = sgn(cp(a-b, d-b));
  int s3 = sgn(cp(c-d, a-d));
  int s4 = sgn(cp(c-d, b-d));
  if(!s1 && !s2 && !s3) return false;
  return s1*s2 <= 0 && s3*s4 <= 0;
}
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

const int N = 100 + 1;
ld ans[N];
int tot[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<ld> xvals;
  vector<pair<pt,pt>> top;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    tot[i] = (x-a) * (b+y);
    pt A(a,b), X(x,y);
    top.push_back(make_pair(A, X));
    xvals.push_back(a);
    xvals.push_back(x);
    for(int j=0; j<i; j++) {
      if(seg_x_seg(top[j].first, top[j].second, A, X)) {
        xvals.push_back(line_inter(top[j].first, top[j].second, A, X).x);
      }
    }
  }
  sort(xvals.begin(), xvals.end());

  for(int i=1; i<xvals.size(); i++) {
    ld s = xvals[i-1];
    ld t = xvals[i];
    if(abs(s-t) < EPS) continue;
    ld m = (s+t) / 2;
    ld l = 0;
    ld r = 0;
    for(int j=0; j<n; j++) {
      const auto& [a, b] = top[j];
      if(m < a.x || m > b.x) continue;
      ld left = line_inter(a, b, pt(s,0), pt(s,1)).y;
      ld right = line_inter(a, b, pt(t,0), pt(t,1)).y;
      if(left + right > l + r) {
        assert(left >= l-EPS && right >= r-EPS);
        ans[j] += (t-s) * (left-l + right-r);
        l = left;
        r = right;
      }
    }
  }

  for(int i=0; i<n; i++) {
    cout << ans[i] / tot[i] << nl;
  }

  return 0;
}

