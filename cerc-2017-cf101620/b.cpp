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
  int x, y, id;
  Point(){}
  Point(int x, int y, int i=0): x(x), y(y), id(i) {}
  bool operator > (const Point& v) const {
    if (x == v.x) return y > v.y;
    else return x > v.x;
  }
  friend ostream& operator << (ostream& os, const Point& v) {
    return os << '(' << v.x << ',' << v.y << ',' << v.id << ')';
  }
};

const int N = 3e5 + 1;
int parent[N];
int value[N];

namespace DSU {
  int root[N];
  void init() { memset(root, -1, sizeof root); }
  int find(int i) {
    if (root[i] == -1) return i;
    return root[i] = find(root[i]);
  }
  // i -> j
  void link(int i, int j) {
    if (find(i) != find(j)) {
      value[find(j)] += value[find(i)];
      root[find(i)] = find(j);
    }
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m, x, y;
  vector<Point> p;

  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> x >> y;
    p.push_back(Point(x,y));
  }

  cin >> m;
  for (int i=1; i<=m; i++) {
    cin >> x >> y;
    p.push_back(Point(x,y,i));
  }

  sort(p.begin(), p.end(), greater<Point>());

  map<int,int> cur; // y-val, id
  for (const Point& it : p) {
    if (!it.id) {
      auto ub = cur.lower_bound(it.y);
      if (ub != cur.end()) {
        value[ub->second]++;
      }
    }
    else {
      auto ub = cur.upper_bound(it.y);
      if (ub != cur.end()) {
        parent[it.id] = ub->second;
      }
      while (ub != cur.begin() && prev(ub)->second > it.id) {
        cur.erase(prev(ub));
      }
      cur.insert(pii(it.y, it.id));
    }
  }

  DSU::init();
  for (int i = m; i >= 1; i--) {
    if (DSU::find(parent[i]) < i) {
      DSU::link(i, parent[i]);
    }
  }

  for (int i = 1; i <= m; i++) {
    cout << value[i] << nl;
  }

  return 0;
}
