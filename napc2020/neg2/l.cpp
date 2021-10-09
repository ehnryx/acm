//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-8;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int R = 6370;
const ld PI = acos((ld)-1);

ld sqr(const ld& x) { return x*x; }

struct p3d {
  ld x, y, z;
  p3d() {}
  p3d(const ld& a, const ld& b, const ld& c): x(a), y(b), z(c) {}
  p3d(ld lon, ld lat) {
    lon = lon * PI / 180;
    lat = lat * PI / 180;
    x = R * cos(lat) * cos(lon);
    y = R * cos(lat) * sin(lon);
    z = R * sin(lat);
  }
  p3d operator + (const p3d& o) const { return p3d(x+o.x, y+o.y, z+o.z); }
  p3d operator - (const p3d& o) const { return p3d(x-o.x, y-o.y, z-o.z); }
  p3d operator * (const ld& c) const { return p3d(x*c, y*c, z*c); }
  p3d operator / (const ld& c) const { return p3d(x/c, y/c, z/c); }
};
ostream& operator << (ostream& os, const p3d& v) {
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
ld norm(const p3d& v) { return sqr(v.x) + sqr(v.y) + sqr(v.z); }
ld abs(const p3d& v) { return sqrt(norm(v)); }
ld dot(const p3d& a, const p3d& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
p3d cross(const p3d& a, const p3d& b) {
  return p3d(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y);
}

ld sdist(const p3d& a, const p3d& b) {
  ld cosang = dot(a, b) / abs(a) / abs(b);
  ld ang = acos(max((ld)-1, min((ld)1, cosang)));
  return ang * R;
}

const int N = 25;
const int M = 2*N*N + N;
const int Q = 100;
int qs[Q], qt[Q], qc[Q];
ld dist[M][M];
ld dj[N];

struct Node {
  int v; ld d;
  bool operator < (const Node& o) const {
    return d > o.d;
  }
};

ld dijkstra(int n, int s, int t, int c) {
  fill(dj, dj+N, -7);
  priority_queue<Node> dijk;
  dijk.push({s, 0});
  while(!dijk.empty()) {
    auto [u, d] = dijk.top();
    dijk.pop();
    if(dj[u] > -1) continue;
    if(u == t) return d;
    dj[u] = d;
    for(int v=0; v<n; v++) {
      if(dj[v] > -1 || dist[u][v] > c) continue;
      dijk.push({v, d + dist[u][v]});
    }
  }
  return -7;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(3);

  for(int n, r, tt=1; cin >> n >> r; tt++) {
    cout << "Case " << tt << ":" << nl;
    const ld rang = (ld)r/R;
    const ld cr = R * sin(rang);
    const ld h = R * cos(rang);
    const ld C = R*2*PI;

    vector<p3d> p;
    for(int i=0; i<n; i++) {
      int lon, lat;
      cin >> lon >> lat;
      p.push_back(p3d(lon, lat));
    }
    int q;
    cin >> q;
    for(int i=0; i<q; i++) {
      cin >> qs[i] >> qt[i] >> qc[i];
      qs[i]--;
      qt[i]--;
    }

    // circle, great circle, in plane of perp
    auto get_points = [=] (const p3d& a, const p3d& b, const p3d& v) {
      ld cosang = dot(a, b) / abs(a) / abs(b);
      ld d = h / cosang;
      p3d center = b / abs(b) * d;
      p3d circ = a / abs(a) * h;
      ld rad2 = sqr(cr) - norm(center - circ);
      p3d dir = cross(v, b);
      dir = dir / abs(dir);
      return make_tuple(center, dir, sqrt(rad2));
    };

    for(int i=0; i<n; i++) {
      for(int j=0; j<i; j++) {
        if(sdist(p[i], p[j]) > 2*r) continue;
        p3d mid = (p[i] + p[j]) / (ld)2;
        auto [center, dir, rad] = get_points(p[i], mid, p[i]);
        p.push_back(center + dir * rad);
        p.push_back(center - dir * rad);
      }
    }

    int all = p.size();
    for(int i=0; i<all; i++) {
      for(int j=0; j<i; j++) {
        dist[i][j] = dist[j][i] = INF;
      }
    }

    auto check_line = [&] (vector<pair<ld,p3d>>& line) {
      sort(line.begin(), line.end(), [] (const auto& a, const auto& b) {
        return a.first < b.first;
      });
      for(int k=1; k<line.size(); k++) {
        p3d mid = line[k-1].second + line[k].second;
        mid = mid / abs(mid) * R;
        bool ok = false;
        for(int t=0; t<n; t++) {
          if(sdist(mid, p[t]) <= r + EPS) {
            ok = true;
            break;
          }
        }
        if(!ok) return false;
      }
      return true;
    };

    for(int i=0; i<all; i++) {
      for(int j=0; j<i; j++) {
        if(abs(cross(p[i], p[j]) / abs(p[i]) / abs(p[j])) < EPS) {
          if(abs(p[i] - p[j]) < 1) {
            dist[i][j] = dist[j][i] = 0;
          }
          continue;
        }
        p3d normal = cross(p[i], p[j]);
        normal = normal / abs(normal);

        vector<pair<ld, p3d>> line, other;
        const ld olen = C - sdist(p[i], p[j]);
        for(int k=0; k<n; k++) {
          p3d tonorm = cross(normal, p[k]) / abs(p[k]);
          if(abs(tonorm) < EPS) continue;
          tonorm = tonorm / abs(tonorm);
          p3d idir = cross(normal, tonorm);
          idir = idir / abs(idir);
          p3d it = idir * (sdist(idir, p[k]) <= r ? R : -R);
          if(sdist(it, p[k]) > r) continue;
          auto [center, dir, rad] = get_points(p[k], it, normal);
          for(const p3d& jt : {center + dir * rad, center - dir * rad}) {
            ld dtoi = sdist(p[i], jt);
            ld dtoj = sdist(p[j], jt);
            if(abs(dtoi + dtoj - sdist(p[i], p[j])) < EPS) {
              line.push_back(make_pair(dtoi, jt));
            } else {
              if(dtoi + dtoj >= olen - EPS) {
                other.push_back(make_pair(dtoi, jt));
              } else if(dtoi < dtoj) {
                other.push_back(make_pair(dtoi, jt));
              } else {
                other.push_back(make_pair(olen - dtoj, jt));
              }
            }
          }
        }
        line.push_back(make_pair((ld)0, p[i]));
        line.push_back(make_pair(sdist(p[i], p[j]), p[j]));
        other.push_back(make_pair((ld)0, p[i]));
        other.push_back(make_pair(olen, p[j]));

        if(check_line(line)) {
          dist[i][j] = dist[j][i] = sdist(p[i], p[j]);
        } else if(check_line(other)) {
          dist[i][j] = dist[j][i] = olen;
        }
      }
    }

    for(int k=0; k<all; k++) {
      for(int i=0; i<all; i++) {
        for(int j=0; j<all; j++) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    for(int i=0; i<q; i++) {
      ld ans = dijkstra(n, qs[i], qt[i], qc[i]);
      if(ans < -1) {
        cout << "impossible" << nl;
      } else {
        cout << ans << nl;
      }
    }

  }

  return 0;
}
