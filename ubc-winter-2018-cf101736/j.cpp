#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct lll {
  static const int L = 30;
  static const int M = (1<<L)-1;
  bool s;
  int a, b; ll c;
  lll(ll x=0, ll y=0) {
    s = ((x<0) ^ (y<0)) && (x!=0 && y!=0);
    x = abs(x);
    y = abs(y);
    ll xa = x & M;
    ll xb = x >> L;
    ll ya = y & M;
    ll yb = y >> L;
    ll va = xa*ya;
    ll vb = (va >> L) + xa*yb + ya*xb;
    ll vc = (vb >> L) + xb*yb;
    a = va & M;
    b = vb & M;
    c = vc;
  }
  bool operator == (const lll& o) const {
    return s==o.s && a==o.a && b==o.b && c==o.c;
  }
  bool operator < (const lll& o) const {
    if(s==o.s) {
      if(c!=o.c) return (c < o.c) ^ s;
      if(b!=o.b) return (b < o.b) ^ s;
      if(a!=o.a) return (a < o.a) ^ s;
      assert(false);
    } else {
      return s;
    }
  }
};

struct Point {
  ll x, y;
  Point(ll _x=0, ll _y=0): x(_x), y(_y) {}
  bool operator < (const Point& o) const {
    return x<o.x || (x==o.x && y<o.y);
  }
  Point operator - (const Point& o) const {
    return Point(x-o.x, y-o.y);
  }
};

ld abs(const Point& v) {
  ld maxv = max(abs(v.x), abs(v.y));
  if(maxv < EPS) {
    return 0;
  } else {
    ld x = v.x / maxv;
    ld y = v.y / maxv;
    return maxv * sqrt(x*x + y*y);
  }
}

int sgncp(const Point& a, const Point& b) {
  lll c = lll(a.x, b.y);
  lll p = lll(b.x, a.y);
  if(c == p) return 0;
  return (c < p ? -1 : 1);
}

bool seg_x_seg(const Point& a, const Point& b, ll x, ll c, ll d) {
  if(max(a.x, b.x) < x || min(a.x, b.x) > x) return false;
  if(a.x == x && b.x == x) return min(a.y, b.y) <= d && max(a.y, b.y) >= c;
  int s1 = sgncp(a-b, Point(x,c)-b);
  int s2 = sgncp(a-b, Point(x,d)-b);
  return s1*s2 <= 0;
}

ll F = 1e9;

vector<int> ex = { -1, -1, 1, 1 };
vector<int> ey = { -1, 1, -1, 1 };

struct Edge {
  int i; ld d;
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

const int N = 4*4*100 + 2;
vector<Edge> adj[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  ll a[n],b[n],x[n],y[n];
  vector<Point> p;
  for(int i=0; i<n; i++) {
    cin>>a[i]>>b[i]>>x[i]>>y[i];
    a[i] *= F;
    b[i] *= F;
    x[i] *= F;
    y[i] *= F;
  }

  auto in_rect = [&] (const Point& v, int j) {
    return a[j] <= v.x && v.x <= x[j] && b[j] <= v.y && v.y <= y[j];
  };

  for(int i=0; i<n; i++) {
    for(int d=0; d<4; d++) {
      {
        Point cur = Point(a[i]+ex[d], b[i]+ey[d]);
        bool ok = true;
        for(int j=0; j<n; j++) {
          if(in_rect(cur, j)) {
            ok = false;
            break;
          }
        }
        if(ok) p.push_back(cur);
      }
      {
        Point cur = Point(a[i]+ex[d], y[i]+ey[d]);
        bool ok = true;
        for(int j=0; j<n; j++) {
          if(in_rect(cur, j)) {
            ok = false;
            break;
          }
        }
        if(ok) p.push_back(cur);
      }
      {
        Point cur = Point(x[i]+ex[d], b[i]+ey[d]);
        bool ok = true;
        for(int j=0; j<n; j++) {
          if(in_rect(cur, j)) {
            ok = false;
            break;
          }
        }
        if(ok) p.push_back(cur);
      }
      {
        Point cur = Point(x[i]+ex[d], y[i]+ey[d]);
        bool ok = true;
        for(int j=0; j<n; j++) {
          if(in_rect(cur, j)) {
            ok = false;
            break;
          }
        }
        if(ok) p.push_back(cur);
      }
    }
  }

  ll sx, sy, tx, ty;
  cin >> sx >> sy >> tx >> ty;
  p.push_back(Point(sx*F, sy*F));
  p.push_back(Point(tx*F, ty*F));
  int m = p.size();
  int S = m-2;
  int T = m-1;

  cerr<<"m: "<<m<<nl;
  vector<Point> q(m);
  for(int i=0; i<m; i++) {
    q[i] = Point(p[i].y, p[i].x);
  }

  cerr<<"running seg_x_seg @ "<<clock()/(ld)CLOCKS_PER_SEC<<nl;

  for(int i=0; i<m; i++) {
    for(int j=0; j<i; j++) {
      bool ok = true;
      for(int k=0; k<n; k++) {
        if(seg_x_seg(p[i], p[j], a[k], b[k], y[k])) {
          ok = false;
          break;
        }
        if(seg_x_seg(p[i], p[j], x[k], b[k], y[k])) {
          ok = false;
          break;
        }
        if(seg_x_seg(q[i], q[j], b[k], a[k], x[k])) {
          ok = false;
          break;
        }
        if(seg_x_seg(q[i], q[j], y[k], a[k], x[k])) {
          ok = false;
          break;
        }
      }
      if(ok) {
        ld d = abs(p[i]-p[j]);
        adj[i].push_back({j, d});
        adj[j].push_back({i, d});
      }
    }
  }

  cerr<<"running dijkstra @ "<<clock()/(ld)CLOCKS_PER_SEC<<nl;

  priority_queue<Edge> dijk;
  vector<ld> dist(m, -2);
  dijk.push({S, 0});
  while(!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if(cur.i == T) {
      cout << cur.d / F << nl;
      return 0;
    }
    if(dist[cur.i] < -1) {
      dist[cur.i] = cur.d;
      for(const Edge& e:adj[cur.i]) {
        dijk.push({e.i, cur.d + e.d});
      }
    }
  }

  cout << -1 << nl;

  return 0;
}
