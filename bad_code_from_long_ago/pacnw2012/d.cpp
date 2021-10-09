#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define ll long long
#define ld double
#define pt complex<ld>
#define pol vector<pt>
#define pii pair<int,int>
#define pdd pair<ld,ld>
#define nl '\n'

const ld EPS = 1e-5;

bool operator < (const pt& a, const pt& b) {
  if (imag(a) != imag(b)) return imag(a) < imag(b);
  else return real(a) < real(b);
}
struct cmp {
  bool operator() (const pt& a, const pt& b) {
    return a < b;
  }
};

pt center;
ld angle(const pt& a) {
  ld aa = arg(a-center);
  return (aa < 0) ? aa + M_PI : aa;
}
bool by_angle(const pt& a, const pt& b) {
  return angle(a) < angle(b);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(0);

  int n, w, h;
  int x, y;
  vector<pt> points;
  set<pt, cmp> half;

  for (;;) {
    cin >> n >> w >> h;
    if (n == 0) 
      break;
    center = pt(w,h);
    points.clear();
    half.clear();
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      points.push_back(pt(x,y));
      if (center < pt(x,y))
        half.insert(pt(x,y));
    }
    sort(points.begin(), points.end(), by_angle);
    for (int i = 0; i < n; i++) {
      int start, end;
      start = i;
      while (i < n-1 && abs(angle(points[i]) - angle(points[i+1])) < EPS) {
        half.erase(points[i]);
        i++;
      }
      half.erase(points[i]);
      end = i;
      if (half.size() <= n/2 && half.size() + end-start+1 >= n/2) {
        for (int j = start; j <= end && half.size() < n/2; j++)
          half.insert(points[j]);
        break;
      } else {
        for (int j = start; j <= end; j++)
          half.insert(points[j]);
      }
    }
    for (const pt& p : half) {
      cout << real(p) << " " << imag(p) << nl;
    }
  }

  return 0;
}
