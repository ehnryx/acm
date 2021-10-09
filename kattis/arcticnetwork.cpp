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

double sqr(double x) { return x*x; }

struct Point {
  double x, y;
  double operator - (const Point& o) const {
    return sqrt(sqr(x-o.x)+sqr(y-o.y));
  }
};

struct Edge {
  int i, j;
  double dist;
  bool operator < (const Edge& o) const {
    return dist < o.dist;
  }
};

const int N = 750+1;
struct DSU {
  int root[N];
  void init(int n) { memset(root, -1, n*sizeof(int)); }
  int find(int i) {
    if (root[i] == -1) return i;
    return root[i] = find(root[i]);
  }
  int link(int i, int j) {
    i = find(i); j = find(j);
    if (i == j) return false;
    root[i] = j;
    return true;
  }
} dsu;

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(2);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int T;
  cin >> T;
  while (T--) {
    int m, n;
    cin >> m >> n;

    vector<Point> p;
    vector<Edge> edges;
    for (int i=0; i<n; i++) {
      double x, y;
      cin >> x >> y;
      p.push_back({x,y});
      for (int j=0; j<i; j++) {
        edges.push_back({i, j, p[i]-p[j]});
      }
    }
    sort(edges.begin(), edges.end());

    dsu.init(n);
    double ans = 0;
    int groups = n;
    for (const Edge& e : edges) {
      if (groups <= m) break;
      if (dsu.link(e.i,e.j)) {
        groups--;
        ans = e.dist;
      }
    }
    cout << ans << nl;
  }

  return 0;
}
