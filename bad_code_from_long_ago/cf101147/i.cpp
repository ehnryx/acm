#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;

struct Point {
  double x;
  ll r;
  int dir;
  Point(double x, ll r, int d): x(x), r(r), dir(d) {}
  bool operator < (const Point& p) const {
    if (abs(p.x-x) < EPS) return dir > p.dir;
    else return x < p.x;
  }
};

int main() {
  freopen("walk.in", "r", stdin);
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  ll x, y, r;
  ll n, m;
  vector<Point> points;

  int T;
  cin >> T;
  while (T--) {
    points.clear();
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> x >> y >> r;
      if (abs(y) <= m - r) {
        double dx = sqrt((m-r)*(m-r) - y*y);
        points.push_back(Point(x - dx, r, 1));
        points.push_back(Point(x + dx, r, -1));
      }
    }
    sort(points.begin(), points.end());

    ll ans = 0;
    ll sum = 0;
    for (const Point& p : points) {
      sum += p.dir * p.r;
      ans = max(ans, sum);
    }
    cout << ans << nl;
  }

  return 0;
}
