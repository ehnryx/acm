#include <bits/stdc++.h>
using namespace std;

typedef long long ld;
typedef long long ll;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-10;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld sgn(const ld& x) { return x; }

struct Segment {
  int a, b, id;
  bool operator < (const Segment& o) const {
    if (a != o.a) return a < o.a;
    else return b < o.b;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;

  while (T--) {
    int n, m; ld x, y;
    cin >> n >> m;

    vector<pt> p;
    for (int i=0; i<n; i++) {
      cin >> x >> y;
      p.push_back(pt(x,y));
    }

    vector<Segment> segs;
    for (int i=1; i<=m; i++) {
      cin >> x >> y;
      pt cur(x,y);
      int front, back;
      front = back = -1;
      for (int j=0; j<n; j++) {
        int pre = (j==0 ? n-1 : j-1);
        int nxt = (j==n-1 ? 0 : j+1);
        if (sgn(cp(p[j]-cur, p[j]-p[pre])) > 0 && sgn(cp(p[j]-cur, p[nxt]-p[j])) < 0) {
          front = j;
        } else if (sgn(cp(p[j]-cur, p[j]-p[pre])) < 0 && sgn(cp(p[j]-cur, p[nxt]-p[j])) > 0) {
          back = j;
        }
      }
      assert(front != -1 && back != -1);
      if (front < back) {
        segs.push_back({front, back, i});
        segs.push_back({front+n, back+n, i});
        segs.push_back({front+2*n, back+2*n, i});
      } else {
        segs.push_back({front, back+n, i});
        segs.push_back({front+n, back+2*n, i});
      }
    }
    sort(segs.begin(), segs.end());
  
    //cerr << "Segments: " << nl; for (const Segment& s : segs) {
      //cerr << s.a << " " << s.b << " " << s.id << nl; }

    int M = m;
    m = segs.size();
    int best = INF;
    vector<int> ans;
    for (int i=0; i<M; i++) {
      vector<int> cur = {segs[i].id};
      int first = segs[i].a;
      int last = segs[i].b;
      int j = i;
      bool bad = 0;
      while (j < m && last < first + n) {
        int bestr = last;
        int bestj = j;
        //cerr << "iter " << j << " " << first << " " << last << nl;
        while (j < m && segs[j].a <= last) {
          if (segs[j].b > bestr) {
            bestr = segs[j].b;
            bestj = j;
          }
          j++;
        }
        if (bestr == last) {
          bad = 1;
          break;
        }
        cur.push_back(segs[bestj].id);
        last = bestr;
      }
      if (!bad && last >= first + n && cur.size() < best) {
        best = cur.size();
        ans = cur;
      }
    }

    if (best == INF) {
      cout << -1 << nl;
    } else {
      cout << ans.size() << nl;
      for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i+1 == ans.size()];
      }
    }
  }

  return 0;
}
