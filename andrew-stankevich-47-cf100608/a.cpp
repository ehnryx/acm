#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m, t, x, y;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    drones.push_back(Point(x,y));
  }

  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> x >> y;
    points.push_back(Point(x,y,true));
  }

  cin >> t;
  for (int i = 0; i < t; i++) {
    cin >> x >> y;
    points.push_back(Point(x,y,false));
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    base = drones[i];
    sort(points.begin(), points.end(), cmp);

    int seen = 0;
    for (const Point& it : points) {
      if (it.target) {
        ans += seen * (t-seen);
      }
    }
  }

  return 0;
}
