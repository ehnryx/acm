#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const int INF = 23592895;
const ld INFA = 1e17L;

const ld PI = acos((ld)-1);
const ld EPS = 1e-12L;

ld sqr(const ld& x) { return x*x; }

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    ll g = abs(__gcd(a,b));
    n = a/g; d = b/g;
    if (d < 0) { n=-n; d=-d; }
  }
  ld val() const { return (ld)n/d; }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
  }
  bool operator != (const Frac& o) const {
    return n*o.d != d*o.n;
  }

  Frac operator + (const Frac& o) const {
    return Frac(n*o.d + d*o.n, d*o.d);
  }
  Frac operator - (const Frac& o) const {
    return Frac(n*o.d - d*o.n, d*o.d);
  }
  Frac operator * (const Frac& o) const {
    return Frac(n*o.n, d*o.d);
  }
  Frac operator / (const Frac& o) const {
    return Frac(n*o.d, d*o.n);
  }
  int sgn() const {
    return (n==0 ? 0 : (n<0 ? -1 : 1));
  }
};

ostream& operator << (ostream& os, const Frac& v) {
  return os << v.n << "/" << v.d;
}

struct Point {
  Frac x, y;
  Point(ll a=0, ll b=0) { x=Frac(a); y=Frac(b); }
  Point(Frac a, Frac b): x(a), y(b) {}
  Point operator - (const Point& o) const {
    return Point(x-o.x, y-o.y);
  }
  bool operator < (const Point& o) const {
    if (x != o.x) return x<o.x;
    else return y<o.y;
  }
  ld argument() const {
    return arg(pt(x.val(),y.val()));
  }
  ld dist() const {
    return sqrt(sqr(x.val())+sqr(y.val()));
  }
  pt val() const {
    return pt(x.val(), y.val());
  }
};

ostream& operator << (ostream& os, const Point& v) {
  return os << "(" << v.x << "," << v.y << ")";
}

Frac cp(const Point& a, const Point& b) {
  return a.x*b.y - a.y*b.x;
}
Frac dp(const Point& a, const Point& b) {
  return a.x*b.x + a.y*b.y;
}

struct Line {
  Point a, b;
  Line(ll c, ll d, ll e, ll f) {
    a = Point(c,d);
    b = Point(e,f);
  }
  bool segx(const Line& o) const {
    int s1 = cp(b-a,o.a-a).sgn();
    int s2 = cp(b-a,o.b-a).sgn();
    int s3 = cp(o.b-o.a,a-o.a).sgn();
    int s4 = cp(o.b-o.a,b-o.a).sgn();
    return s1*s2 <= 0 && s3*s4 <= 0;
  }
  Point inter(const Line& o) const {
    Frac f = cp(o.a-a,o.b-o.a)/cp(b-a,o.b-o.a);
    return Point(a.x + f*(b.x-a.x), a.y + f*(b.y-a.y));
  }
  ld angle() const {
    return (b-a).argument();
  }
  bool contains(const Point& v) const {
    return abs((a-v).dist() + (b-v).dist() - (a-b).dist()) < EPS;
  }
  ld dist(const Point& v) const {
    ld d = (v-a).dist();
    return (Frac(0,1) < dp(v-a,b-a) ? d : -d);
  }
};

ld opposite(const ld& x) {
  return (x>0 ? x-PI : x+PI);
}

ld cpp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dpp(const pt& a, const pt& b) { return real(conj(a)*b); }

bool pt_in_polygon(const pt& p, const pol& v) {
  ld res = 0; int n = v.size();
  for (int i=n-1,j=0; j<n; i=j++) {
    res += atan2(cpp(v[i]-p,v[j]-p), dpp(v[i]-p,v[j]-p));
  }
  return res < -1;
}

ld area(const pol& v) {
  ld s=0; int n=v.size();
  for (int i=n-1,j=0; j<n; i=j++) s += cpp(v[i],v[j]);
  return s;
}

struct Edge {
  int id; ld ang;
  bool operator < (const Edge& o) const {
    return ang < o.ang;
  }
};

struct EdgeF {
  int id, d;
};

const int N = 100*100+7;
vector<Edge> graph[N];
vector<EdgeF> adj[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int m, x0, y0, x1, y1;
  cin >> m >> x0 >> y0 >> x1 >> y1;

  pt start(x0,y0);
  pt end(x1,y1);

  vector<Point> verts;
  vector<Line> lines;

  auto insert_point = [&] (const Point& v) {
    for (const Point& it : verts) {
      if ((it-v).dist() < EPS) return;
    }
    verts.push_back(v);
  };

  for (int i=0; i<m; i++) {
    int xa, ya, xb, yb;
    cin >> xa >> ya >> xb >> yb;
    lines.push_back({xa,ya,xb,yb});
    for (int j=0; j<i; j++) {
      if (lines[i].segx(lines[j])) {
        insert_point(lines[i].inter(lines[j]));
      }
    }
  }

  int n = verts.size();
  for (const Line& it : lines) {
    vector<pair<ld,int>> points;
    cerr << it.a.val() << " " << it.b.val() << " -> " << nl;
    for (int i=0; i<n; i++) {
      if (it.contains(verts[i])) {
        points.push_back({it.dist(verts[i]),i});
        cerr << "  contains " << verts[i].val() << nl;
      }
    }
    sort(points.begin(), points.end());
    ld ang = it.angle();
    for (int i=1; i<points.size(); i++) {
      int a = points[i-1].second;
      int b = points[i].second;
      graph[a].push_back({b,ang});
      graph[b].push_back({a,opposite(ang)});
    }
  }

  unordered_map<int,int> nxt[n];
  for (int i=0; i<n; i++) {
    sort(graph[i].begin(), graph[i].end());
    for (int j=0; j<graph[i].size(); j++) {
      int pj = (j==0 ? graph[i].size()-1 : j-1);
      nxt[i][graph[i][pj].id] = graph[i][j].id;
    }
    cerr << i << ": " << verts[i].val() << " -> "; for (const Edge& e : graph[i])
    cerr << verts[e.id].val() << "  ";
    cerr << nl;
  }

  set<pii> vis;
  int face = 0;
  map<pii,int> edges;

  auto add_edge = [&] (int a, int b, int f) {
    pii e(a,b), r(b,a);
    vis.insert(e);
    if (edges.count(r)) {
      adj[edges[r]].push_back({f,1});
      adj[f].push_back({edges[r],1});
    } else {
      edges[e] = f;
    }
  };

  int s = -1;
  int t = -1;
  ld sarea = INFA;
  ld tarea = INFA;
  vector<int> outside;

  vector<pol> poly;

  cerr << "FACES" << nl;
  for (int i=0; i<n; i++) {
    for (const Edge& e : graph[i]) {
      if (!vis.count(pii(i,e.id))) {
        pol p = { verts[i].val() };
        int pre = i;
        int cur = e.id;
        while (cur != i) {
          p.push_back(verts[cur].val());
          add_edge(pre, cur, face);
          int to = nxt[cur][pre];
          pre = cur;
          cur = to;
        }
        add_edge(pre, cur, face);
        ld a = area(p);
        if (pt_in_polygon(start, p) && abs(a) < sarea) {
          s = face;
          sarea = abs(a);
        }
        if (pt_in_polygon(end, p) && abs(a) < tarea) {
          t = face;
          tarea = abs(a);
        }
        if (a > 0) {
          outside.push_back(face);
        }
        poly.push_back(p);
        cerr << face << ": "; for (const pt& it : p) {
          cerr << it << " "; }
        cerr << nl;
        face++;
      }
    }
  }

  if (face == 0) {
    cout << 0 << nl;
    return 0;
  }

  assert(!outside.empty());
  int exterior = face;
  for (int it : outside) {
    cerr << "OUTSIDE " << it << endl;
    int connect = face;
    ld best = INFA;
    ld farea = abs(area(poly[it]));
    for (int j=0; j<face; j++) {
      const pol& p = poly[j];
      ld a = abs(area(p));
      if (a < farea + 0.25) continue;
      if (pt_in_polygon(poly[it][0], p) && a < best) {
        cerr << " FOUND " << j << endl;
        best = a;
        connect = j;
      }
    }
    adj[it].push_back({connect,0});
    adj[connect].push_back({it,0});
  }
  if (s==-1) s = exterior;
  if (t==-1) t = exterior;

  vector<int> dis(N, INF);
  dis[s] = 0;
  deque<int> bfs;
  bfs.push_front(s);
  while (!bfs.empty()) {
    int u = bfs.front(); bfs.pop_front();
    if (u == t) {
      cout << dis[t] << nl;
      return 0;
    }
    for (const EdgeF e : adj[u]) {
      if (dis[u]+e.d < dis[e.id]) {
        dis[e.id] = dis[u]+e.d;
        if (e.d) bfs.push_back(e.id);
        else bfs.push_front(e.id);
      }
    }
  }

  assert(false);

  return 0;
}
