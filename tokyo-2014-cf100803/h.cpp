#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

#define polar(r,a) (pt){r*cos(a),r*sin(a)}

typedef complex<ld> pt;
typedef pair<pt,pt> ppt;
const ld PI = acos((ld)-1);
const ld EPS = 1e-9;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
ld lsp_dist(const pt& a, const pt& b, const pt& p) {
  return dp(b-a,p-a)>0 && dp(a-b,p-b)>0 ? 
    abs(cp(b-a,p-a)/abs(b-a)) : min(abs(a-p),abs(b-p));
}

ppt circle_tangent(ld r1, ld r2, ld d, int k) {
  ld dr=(k&2)?(-r1-r2) : (r2-r1); ld t=asin(dr/d);
  pt p1=polar(r1,PI/2+t), p2=polar(r2,PI/2+t); if (k&2) p2*=-1; p2+=pt(d,0);
  if (k&1) { p1=pt(p1.real(),-p1.imag()); p2=pt(p2.real(),-p2.imag()); }
  return make_pair(p1,p2);
}
ppt circle_tangent(pt p1, ld r1, pt p2, ld r2, int k) {
  pt d=p2-p1; ppt p=circle_tangent(r1,r2,abs(d),k); d/=abs(d);
  p.first *= d; p.second *= d; p.first += p1; p.second += p1; return p;
}

struct Circle {
  pt c; ld r;
};

struct Edge {
  int cc, id;
  ld dist;
  bool operator < (const Edge& o) const {
    return dist > o.dist;
  }
};

const int N = 10;
vector<Circle> circ;
vector<pt> p[N];
//vector<Edge> adj[N][N*4];
ld adj[N][N*4][N][N*4];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);

  for (int i=0; i<N; i++) {
    for (int ii=0; ii<N*4; ii++) {
      for (int j=0; j<N; j++) {
        for (int jj=0; jj<N*4; jj++) {
          adj[i][ii][j][jj] = 1e42;
        }
      }
    }
  }

  int n, x, y;
  cin >> n >> x >> y;

  n += 2;
  circ.push_back({pt(0,0),0});
  circ.push_back({pt(x,y),0});
  for (int i=2; i<n; i++) {
    cin >> x >> y;
    circ.push_back({pt(x,y),100});
  }

  //cerr << "Circle tangents" << endl;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i==j) continue;
      int lim = 4;
      if (abs(circ[i].c-circ[j].c) < circ[i].r+circ[j].r) lim = 2;
      for (int k=0; k<lim; k++) {
        ppt seg = circle_tangent(circ[i].c, circ[i].r, circ[j].c, circ[j].r, k);
        assert(seg==seg);
        bool ok = true;
        for (const pt& it : p[i]) {
          if (abs(it-seg.first) < EPS) {
            ok = false;
          }
        }
        for (int c=0; c<n; c++) {
          if (c==i) continue;
          if (abs(circ[c].c-seg.first) < circ[c].r) {
            ok = false;
          }
        }
        if (ok) {
          p[i].push_back(seg.first);
        }
      }
    }
    assert(p[i].size() < 4*n);
  }

  //cerr << "Circle distance" << endl;
  for (int i=2; i<n; i++) {
    vector<pair<ld,int>> idx;
    for (int j=0; j<p[i].size(); j++) {
      const pt& it = p[i][j];
      ld ang = arg(it-circ[i].c);
      idx.push_back(make_pair(ang,j));
      idx.push_back(make_pair(ang+2*PI,j));
    }
    for (int j=2; j<n; j++) {
      if (i==j) continue;
      if (abs(circ[i].c-circ[j].c) < circ[i].r+circ[j].r) {
        ld ang = arg(circ[j].c-circ[i].c);
        idx.push_back(make_pair(ang,-1));
        idx.push_back(make_pair(ang+2*PI,-1));
      }
    }
    sort(idx.begin(), idx.end());
    for (int j=1; j<idx.size(); j++) {
      if (idx[j].second != -1 && idx[j-1].second != -1 && idx[j].second != idx[j-1].second) {
        ld d = circ[i].r * (idx[j].first-idx[j-1].first);
        adj[i][idx[j].second][i][idx[j-1].second] = d;
        adj[i][idx[j-1].second][i][idx[j].second] = d;
      }
    }
  }

  //cerr << "Tangent distance" << endl;
  for (int i=0; i<n; i++) {
    for (int ii=0; ii<p[i].size(); ii++) {
      for (int j=0; j<n; j++) {
        for (int jj=0; jj<p[j].size(); jj++) {
          bool ok = true;
          for (int k=0; k<n; k++) {
            ld d = lsp_dist(p[i][ii], p[j][jj], circ[k].c);
            if (d < circ[k].r-EPS) {
              ok = false;
            }
          }
          if (ok) {
            adj[i][ii][j][jj] = abs(p[i][ii]-p[j][jj]);
          }
        }
      }
    }
  }

  //cerr << "Trivial" << endl;
  for (int k=0; k<n; k++) {
    for (int kk=0; kk<p[k].size(); kk++) {
      for (int i=0; i<n; i++) {
        for (int ii=0; ii<p[i].size(); ii++) {
          for (int j=0; j<n; j++) {
            for (int jj=0; jj<p[j].size(); jj++) {
              adj[i][ii][j][jj] = min(adj[i][ii][j][jj], adj[i][ii][k][kk]+adj[k][kk][j][jj]);
            }
          }
        }
      }
    }
  }

  assert(p[0].size()==1);
  assert(p[1].size()==1);
  if (adj[0][0][1][0] > 1e40) {
    cout << "0.0" << nl;
  } else {
    cout << adj[0][0][1][0] << nl;
  }

  return 0;
}
