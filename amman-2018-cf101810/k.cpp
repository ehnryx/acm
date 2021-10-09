#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos(-1.L);

struct Point {
  ld x;
  int t;
  Point(){}
  Point(ld x, int t): x(x), t(t) {}
  bool operator < (const Point& v) const {
    return x < v.x;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;

  while (T--) {
    int n, m;
    ld z;
    cin >> n >> m >> z;
    ld radius = z/2;

    vector<Point> vals;
    int a, b;
    for (int i=0; i<n; i++) {
      cin >> a >> b;
      pt p(a,b);
      ld s, t;
      ld d = abs(p);
      if (d <= radius) {
        s = arg(p*pt(0,-1));
        t = arg(p*pt(0,1));
      }
      else {
        ld ang = asin(radius/d);
        s = arg(p*exp(pt(0,-ang)));
        t = arg(p*exp(pt(0,ang)));
      }
      s -= EPS;
      t += EPS;
      if (s < 0) s += 2*PI;
      if (t < 0) t += 2*PI;

      vals.push_back(Point(s, 1));
      vals.push_back(Point(t+2*PI, -1));
      if (s < t) {
        vals.push_back(Point(s+2*PI, 1));
        vals.push_back(Point(t, -1));
      }
    }
    sort(vals.begin(), vals.end());

    bool good = false;
    int cnt = 0;
    for (const Point& it : vals) {
      cnt += it.t;
      //cerr << it.x << " -> " << cnt << nl;
      if (cnt >= m) {
        good = true;
        break;
      }
    }

    cout << (good ? "Yes" : "No") << nl;
  }

  return 0;
}
