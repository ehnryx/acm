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

struct Point {
  int s, e;
  Point() {}
  Point(int s, int e): s(s), e(e) {}
  bool operator < (const Point& v) const {
    if (e == v.e) return s < v.s;
    else return e < v.e;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  vector<Point> p;
  int a, b;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    p.push_back(Point(a,b));
  }
  sort(p.begin(), p.end());

  vector<int> ans;
  int cur = -INF;
  for (const Point& it : p) {
    if (it.s <= cur) continue;
    cur = it.e;
    ans.push_back(cur);
  }

  cout << ans.size() << nl;
  for (int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
