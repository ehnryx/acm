#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef double ld;
typedef pair<int,int> pii;

const ld INF = 1e9;
const ld EPS = 1e-6;

inline ld sqr(const ld& x) { return x*x; }

struct p3d {
  ld x, y, z;
  ld dsqr(const p3d& o) const {
    return sqr(x-o.x)+sqr(y-o.y)+sqr(z-o.z);
  }
};

struct Point {
  int x, y, z, vx, vy, vz;
  p3d get(ld t) const {
    return { x+vx*t, y+vy*t, z+vz*t };
  }
};

struct Edge {
  int a, b; ld c;
  bool operator < (const Edge& o) const {
    return c < o.c;
  }
};

const int N = 50;
int root[N];
void reset() {
  memset(root, -1, sizeof root);
}
int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}
bool link(int i, int j) {
  i = find(i); j = find(j);
  if (i == j) return false;
  root[i] = j;
  return true;
}

vector<pii> mst(ld t, const vector<Point>& p) {
  int n = p.size();
  vector<Edge> edges;
  for (int i=0; i<n; i++) {
    for (int j=0; j<i; j++) {
      edges.push_back({i, j, p[i].get(t).dsqr(p[j].get(t))});
    }
  }
  sort(edges.begin(), edges.end());

  reset();
  vector<pii> out;
  for (const Edge& e : edges) {
    if (link(e.a, e.b)) {
      out.push_back(pii(e.a,e.b));
      if (out.size() == n-1) break;
    }
  }
  sort(out.begin(), out.end());
  return out;
}

int solve(ld left, ld right, const vector<pii>& lval, const vector<pii>& rval, const vector<Point>& p) {
  if (right-left < EPS) return 1;
  ld mid = (left+right)/2;
  vector<pii> mval = mst(mid, p);
  int res = 0;
  if (mval != lval) res += solve(left, mid, lval, mval, p);
  if (mval != rval) res += solve(mid, right, mval, rval, p);
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int n, tt=1; cin >> n; tt++) {
    cout << "Case " << tt << ": ";
    vector<Point> p;
    for (int i=0; i<n; i++) {
      int x, y, z, vx, vy, vz;
      cin >> x >> y >> z >> vx >> vy >> vz;
      p.push_back({x,y,z,vx,vy,vz});
    }

    ld left = 0;
    ld right = INF;
    vector<pii> lval = mst(left, p);
    vector<pii> rval = mst(right, p);
    if (lval == rval) cout << 1 << nl;
    else cout << 1 + solve(left, right, lval, rval, p) << nl;
  }

  return 0;
}
