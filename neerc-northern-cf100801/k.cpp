#include <bits/stdc++.h>
using namespace std;

#define FILENAME "kingdom"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int INF = 0x3f3f3f3f;
const ld EPS = 1e-13;
const ld PI = acos((ld)-1);

struct Point {
  int x, y;
  Point(int _x, int _y): x(_x), y(_y) {}
  ld angle(const Point& o) const {
    return atan2((ld)o.y-y, (ld)o.x-x);
  }
  ld dist(const Point& o) const {
    return sqrt((ld)(x-o.x)*(x-o.x) + (ld)(y-o.y)*(y-o.y));
  }
  ll norm(const Point& o) const {
    return (ll)(x-o.x)*(x-o.x) + (ll)(y-o.y)*(y-o.y);
  }
};

struct Range {
  ld l, r;
  Range(): l(-2*PI), r(2*PI) {}
  bool contains(const ld& x) const {
    return (l-EPS <= x && x <= r+EPS)
      || (l-EPS <= x+2*PI && x+2*PI <= r+EPS)
      || (l-EPS <= x-2*PI && x-2*PI <= r+EPS);
  }
  void intersect(ld a, ld b) {
    if(!(r+EPS < a || b < l-EPS)) {
    } else if(!(r+EPS < a+2*PI || b+2*PI < l-EPS)) {
      a += 2*PI;
      b += 2*PI;
    } else if(!(r+EPS < a-2*PI || b-2*PI < l-EPS)) {
      a -= 2*PI;
      b -= 2*PI;
    }
    l = max(l, a);
    r = min(r, b);
  }
};

struct AdjGraph : vector<vector<bool>> {
  AdjGraph(const vector<Point>& p, ll d) {
    int n = p.size();
    resize(n, vector<bool>(n, false));
    for(int i=0; i<n; i++) {
      Range cur;
      for(int j=i+1; j<n; j++) {
        if(cur.contains(p[i].angle(p[j]))) {
          (*this)[i][j] = (*this)[j][i] = true;
        }
        if(p[i].norm(p[j]) > d*d) {
          ld mid = p[i].angle(p[j]);
          ld add = asin(d / p[i].dist(p[j]));
          cur.intersect(mid-add, mid+add);
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  int n, d;
  cin >> n >> d;
  vector<Point> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.push_back(Point(x,y));
  }

  AdjGraph forward(p, d);
  reverse(p.begin(), p.end());
  AdjGraph backward(p, d);

  vector<int> dp(n, INF);
  dp[0] = 1;
  for(int i=1; i<n; i++) {
    for(int j=0; j<i; j++) {
      if(forward[i][j] && backward[n-1-i][n-1-j]) {
        dp[i] = min(dp[i], dp[j] + 1);
      }
    }
  }
  cout << dp[n-1] << nl;

  return 0;
}
