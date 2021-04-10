#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
#pragma GCC target("avx,sse4")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef /*long*/ double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
template <typename T> inline void read(T &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

struct Point {
  int x, y;
  Point(int _x=0, int _y=0): x(_x), y(_y) {}
  Point operator - (const Point& o) const {
    return Point(x - o.x, y - o.y);
  }
};

ld abs(const Point& v) {
  return sqrt((ll)v.x*v.x + (ll)v.y*v.y);
}

ll dot(const Point& a, const Point& b) {
  return (ll)a.x*b.x + (ll)a.y*b.y;
}

ll cross(const Point& a, const Point& b) {
  return (ll)a.x*b.y - (ll)a.y*b.x;
}

ld lsp_dist(const Point& a, const Point& b, const Point& p) {
  return dot(b - a, p - a) > 0 && dot(a - b, p - b) > 0 ?
    abs(cross(b - a, p - a)) / abs(b - a) : min(abs(a - p), abs(b - p));
}

bool pt_in_polygon(const Point &p, const vector<Point> &v) {
  int n = v.size();
  ld res = 0; for(int i = n-1, j = 0; j < n; i = j++) {
    res += atan2(cross(v[i] - p, v[j] - p), dot(v[i] - p, v[j] - p));
  }
  return abs(res) > 1;
}

ll area(const vector<Point>& v) {
  ll s = 0;
  int n = v.size();
  for(int i=n-1, j=0; j<n; i=j++) {
    s += cross(v[i], v[j]);
  }
  return s;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  //cin >> n;
  read(n);

  vector<int> inner(n), outer(n);
  vector<tuple<int,int,int>> leftmost;
  pair<ll,int> cover(INFLL, INFLL);

  ld ans = INFLL;
  for(int i=0; i<n; i++) {
    //cin >> outer[i] >> inner[i];
    read(outer[i]); read(inner[i]);
    int m;
    //cin >> m;
    read(m);
    vector<Point> v;
    for(int j=0; j<m; j++) {
      int x, y;
      //cin >> x >> y;
      read(x); read(y);
      v.emplace_back(x, y);
      leftmost.emplace_back(x, y, i);
    }
    for(int j=m-1, k=0; k<m; j=k++) {
      ld d = lsp_dist(v[j], v[k], Point(0, 0));
      ll h = min(inner[i], outer[i]);
      ans = min(ans, sqrt(d*d + h*h));
    }
    if(pt_in_polygon(Point(0, 0), v)) {
      cover = min(cover, pair(abs(area(v)), inner[i]));
    }
  }

  if(cover.first < INFLL) {
    ans = min(ans, (ld)cover.second);
  } else {
    sort(begin(leftmost), end(leftmost));
    ans = min(ans, (ld)outer[get<2>(leftmost.front())]);
  }

  cout << ans << nl;

  return 0;
}
