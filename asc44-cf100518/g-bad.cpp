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

const int N = 1<<16;

struct SegTree {
  int segt[2*N], best[2*N], minv[2][2*N], maxv[2][2*N], lazy[2][2*N];

  void reset() {
    memset(best, 0, sizeof best);
    memset(segt, 0, sizeof segt);
    memset(minv, 0, sizeof minv);
    memset(maxv, 0, sizeof minv);
    memset(lazy, 0, sizeof lazy);
  }

  void push(int id, int i) {
    if (lazy[id][i]) {
      segt[2*i] += lazy[id][i];
      segt[2*i+1] += lazy[id][i];
      minv[id][2*i] += lazy[id][i];
      minv[id][2*i+1] += lazy[id][i];
      maxv[id][2*i] += lazy[id][i];
      maxv[id][2*i+1] += lazy[id][i];
      lazy[id][2*i] += lazy[id][i];
      lazy[id][2*i+1] += lazy[id][i];
      lazy[id][i] = 0;
    }
  }

  void pull(int id, int i) {
    if (segt[2*i] > segt[2*i+1]) {
      best[i] = best[2*i];
    } else {
      best[i] = best[2*i+1];
    }
    segt[i] = max(segt[2*i], segt[2*i+1]);
    minv[id][i] = min(minv[id][2*i], minv[id][2*i+1]);
    maxv[id][i] = max(maxv[id][2*i], maxv[id][2*i+1]);
  }

  void insert(int id, int l, int r, int i=1, int s=0, int e=N-1) {
    if (r<s || e<l) return;
    if (l<=s && e<=r && minv[id][i] == maxv[id][i]) {
      segt[i]++;
      if (s==e) best[i] = s;
      minv[id][i]++;
      maxv[id][i]++;
      lazy[id][i]++;
      return;
    }
    push(id,i);
    int m = (s+e)/2;
    insert(id, l, r, 2*i, s, m);
    insert(id, l, r, 2*i+1, m+1, e);
    pull(id,i);
  }

  pii query(int l, int r, int i=1, int s=0, int e=N-1) {
    if (r<s || e<l) return { -INF, -1 };
    if (l<=s && e<=r) {
      return { segt[i], best[i] };
    }
    push(0,i); push(1,i);
    int m = (s+e)/2;
    return max(query(l, r, 2*i, s, m), query(l, r, 2*i+1, m+1, e));
  }
};

SegTree segtree[2];

struct Point {
  int x, y, c;
  void rotate() {
    int nx = -y;
    y = x;
    x = nx;
  }
  bool operator < (const Point& o) const {
    return x < o.x;
  }
};

ostream& operator << (ostream& os, const Point& v) {
  return os << v.x << " " << v.y;
}

struct Rectangle {
  Point a, b;
  void fix() {
    int minx = min(a.x, b.x);
    int miny = min(a.y, b.y);
    int maxx = max(a.x, b.x);
    int maxy = max(a.y, b.y);
    a = { minx, miny };
    b = { maxx, maxy };
  }
};

ostream& operator << (ostream& os, const Rectangle& v) {
  return os << v.a << " " << v.b;
}

Rectangle val[3];
int cnt[3];
int ans;

const int BIG = 2e9;

void solve(vector<Point> p, int rot) {
  int n = p.size();

  map<int,int> remap;
  memset(cnt, 0, sizeof cnt);
  for (auto& it : p) {
    for (int i=0; i<rot; i++) {
      it.rotate();
    }
    cnt[it.c]++;
    remap[it.y];
  }
  p.push_back({BIG-1, BIG-7, -1});

  int decmp[n+7];
  int rmpid = 0;
  for (auto& it : remap) {
    it.second = rmpid;
    decmp[rmpid] = it.first;
    rmpid++;
  }
  int ub = rmpid-1;

  sort(p.begin(), p.end());

  bool updated = false;

  for (int c=0; c<3; c++) {
    segtree[0].reset();
    segtree[1].reset();
    int pre = -BIG+7;
    int curcnt = 0;

    for (int i=0; i<=n; i++) {
      const auto& it = p[i];

      if (it.x != pre) {
        int res, best;

        tie(res, best) = segtree[0].query(0, ub);
        res += cnt[c];
        if (res > ans) {
          //cerr << "1 UPD " << ans << " to " << res << " w/ " << pre << "," << decmp[best] << " at r,c " << rot << " " << c << "   FROM " << res-cnt[c] << " + " << cnt[c] << endl;
          updated = true;
          ans = res;
          val[c] = { { pre, -BIG }, { BIG, BIG } };
          val[c==0?1:0] = { { -BIG, decmp[best] }, { pre, BIG } };
          val[c==2?1:2] = { { -BIG, -BIG }, { pre, decmp[best] } };
        }

        tie(res, best) = segtree[1].query(0, ub);
        res += cnt[c];
        if (res > ans) {
          //cerr << "2 UPD " << ans << " to " << res << " w/ " << pre << "," << decmp[best] << " at r,c " << rot << " " << c << "   FROM " << res-cnt[c] << " + " << cnt[c] << endl;
          updated = true;
          ans = res;
          val[c] = { { pre, -BIG }, { BIG, BIG } };
          val[c==2?1:2] = { { -BIG, decmp[best] }, { pre, BIG } };
          val[c==0?1:0] = { { -BIG, -BIG }, { pre, decmp[best] } };
        }

        cnt[c] -= curcnt;
        curcnt = 0;
        if (i==n) break;
      }

      if (it.c == c) {
        curcnt++;
      } else {
        int cid = it.c - (it.c>c);
        if (cid == 0) {
          segtree[0].insert(cid, 0, remap[it.y]);
          segtree[1].insert(cid, remap[it.y], ub);
        } else if (cid == 1) {
          segtree[0].insert(cid, remap[it.y], ub);
          segtree[1].insert(cid, 0, remap[it.y]);
        }
      }

      pre = it.x;
    }
  }

  if (updated) {
    for (auto& it : val) {
      for (int i=rot; i<4; i++) {
        it.a.rotate();
        it.b.rotate();
      }
      it.fix();
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen("gold.in", "r", stdin);
  freopen("gold.out", "w", stdout);
#endif

  for (int n; cin >> n && n; ) {
    vector<Point> p;
    for (int i=0; i<n; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      p.push_back({a,b,c});
    }

    ans = 0;
    for (int rot=0; rot<4; rot++) {
      solve(p, rot);
    }
    cout << ans << nl;
    for (int i=0; i<3; i++) {
      cout << val[i].a.x << " " << val[i].a.y << " ";
      cout << val[i].b.x << " " << val[i].b.y << nl;
    }
  }

  return 0;
}
