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
const ld EPS = 1e-9;

struct Point {
  int a, b;
  Point(int a, int b): a(a), b(b) {}
  bool operator < (const Point& p) const {
    return b < p.b;
  }
};

bool cmp_a(const Point& a, const Point& b) {
  return a.a < b.a;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  vector<Point> points;
  int a, b;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    points.push_back(Point(a,b));
  }
  sort(points.begin(), points.end(), cmp_a);

  int curId = 0;
  vector<Point> sorted;
  priority_queue<Point> available;
  for (int i = 0; i <= n; i++) {
    while (curId < n && points[curId].a <= i) {
      available.push(points[curId]);
      curId++;
    }
    if (!available.empty()) {
      sorted.push_back(available.top());
      available.pop();
    }
  }
  while (!available.empty()) {
    sorted.push_back(available.top());
    available.pop();
  }

  int ans = 0;
  int cur = 0;
  for (int i = 0; i < sorted.size(); i++) {
    if (cur < sorted[i].a) {
      ans += sorted.back().b;
      sorted.pop_back();
      --i;
    }
    cur++;
  }

  cout << ans << nl;

  return 0;
}
