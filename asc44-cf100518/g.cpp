#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef pair<int,int> pii;

const int BIG = 2e9;
const int INF = 0x3f3f3f3f;

const int N = 1<<16;
namespace SegTree {
  pii rmq[2*N];
  int lazy[2*N];
  void reset(int n) {
    for (int i=0; i<n; i++) {
      rmq[n+i] = { 0, i };
      lazy[n+i] = 0;
    }
    for (int i=n-1; i>0; i--) {
      rmq[i] = max(rmq[2*i], rmq[2*i+1]);
      lazy[i] = 0;
    }
  }

  void push(int i) {
    if (lazy[i]) {
      rmq[2*i].first += lazy[i];
      rmq[2*i+1].first += lazy[i];
      lazy[2*i] += lazy[i];
      lazy[2*i+1] += lazy[i];
      lazy[i] = 0;
    }
  }
  void pull(int i) {
    rmq[i] = max(rmq[2*i], rmq[2*i+1]);
  }

  void insert(int l, int r, int i, int s, int e) {
    if (r<s || e<l) return;
    if (l<=s && e<=r) {
      rmq[i].first++;
      lazy[i]++;
      return;
    }
    push(i);
    int m = (s+e)/2;
    insert(l, r, 2*i, s, m);
    insert(l, r, 2*i+1, m+1, e);
    pull(i);
  }
  pii query(int l, int r, int i, int s, int e) {
    if (r<s || e<l) return { -INF, -1 };
    if (l<=s && e<=r) return rmq[i];
    push(i);
    int m = (s+e)/2;
    return max(query(l, r, 2*i, s, m), query(l, r, 2*i+1, m+1, e));
  }
}

struct Point {
  int x, y, c;
  bool operator < (const Point& o) const {
    return x < o.x;
  }
  void rotate() {
    int nx = -y;
    y = x;
    x = nx;
  }
};

struct Rectangle {
  Point a, b;
  void rotate() {
    a.rotate();
    b.rotate();
  }
  void fix() {
    int minx = min(a.x, b.x);
    int miny = min(a.y, b.y);
    int maxx = max(a.x, b.x);
    int maxy = max(a.y, b.y);
    a = { minx, miny };
    b = { maxx, maxy };
  }
};

int np2;
int ans;
Rectangle sol[3];
int cnt[3];

void solveT(vector<Point> p, int rot) {
  int n = p.size();

  map<int,int> remap;
  vector<int> decmp;
  memset(cnt, 0, sizeof cnt);
  for (Point& it : p) {
    for (int i=0; i<rot; i++) {
      it.rotate();
    }
    remap[it.y];
    cnt[it.c]++;
  }
  p.push_back({BIG-7});

  int rmpid = 0;
  for (auto& it : remap) {
    decmp.push_back(it.first);
    it.second = rmpid++;
  }
  int ub = rmpid-1;

  sort(p.begin(), p.end());

  bool updated = false;

  vector<int> c = {0,1,2};
  do {
    SegTree::reset(np2);
    int pre = -BIG+7;
    int curcnt = 0;
    int seen = 0;
    for (int i=0; i<=n; i++) {
      const auto& it = p[i];

      if (it.x != pre) {
        int res, best;
        tie(res, best) = SegTree::query(0, ub, 1, 0, np2-1);
        res += cnt[c[0]] - seen;
        if (res > ans) {
          updated = true;
          ans = res;
          sol[c[0]] = { { pre, -BIG }, { BIG, BIG } };
          sol[c[1]] = { { -BIG, -BIG }, { pre, decmp[best] } };
          sol[c[2]] = { { -BIG, decmp[best] }, { pre, BIG } };
        }
        seen += curcnt;
        curcnt = 0;
        if (i==n) break;
      } else {
        assert(i!=n);
      }

      if (it.c == c[0]) {
        curcnt++;
      } else if (it.c == c[1]) {
        SegTree::insert(remap[it.y], ub, 1, 0, np2-1);
      } else {
        assert(it.c == c[2]);
        SegTree::insert(0, remap[it.y], 1, 0, np2-1);
      }

      pre = it.x;
    }
  } while (next_permutation(c.begin(), c.end()));

  if (updated) {
    for (Rectangle& rect : sol) {
      for (int i=rot; i<4; i++) {
        rect.rotate();
      }
      rect.fix();
    }
  }
}

void solve3(vector<Point> p, int rot) {
  int n = p.size();

  map<int,int> remap;
  vector<int> decmp;
  memset(cnt, 0, sizeof cnt);
  for (Point& it : p) {
    for (int i=0; i<rot; i++) {
      it.rotate();
    }
    remap[it.x];
    cnt[it.c]++;
  }
  p.push_back({BIG-7});
  remap[-BIG+7];

  int rmpid = 0;
  for (auto& it : remap) {
    decmp.push_back(it.first);
    it.second = rmpid++;
  }
  int ub = rmpid-1;

  sort(p.begin(), p.end());

  bool updated = false;

  vector<int> c = {0,1,2};
  do {
    SegTree::reset(np2);
    int pre = -BIG+7;
    int curcnt = 0;
    int seen = 0;
    for (int i=0; i<=n; i++) {
      const auto& it = p[i];

      if (it.x != pre && pre > -BIG+7) {
        int res, best;
        tie(res, best) = SegTree::query(0, remap[pre]-1, 1, 0, np2-1);
        res += cnt[c[0]] - seen;
        if (res > ans) {
          updated = true;
          ans = res;
          sol[c[0]] = { { pre, -BIG }, { BIG, BIG } };
          sol[c[1]] = { { -BIG, -BIG }, { decmp[best], BIG } };
          sol[c[2]] = { { decmp[best], -BIG }, { pre, BIG } };
        }
        seen += curcnt;
        curcnt = 0;
        if (i==n) break;
      } else {
        assert(i!=n);
      }

      if (it.c == c[0]) {
        curcnt++;
      } else if (it.c == c[1]) {
        SegTree::insert(remap[it.x], ub, 1, 0, np2-1);
      } else if (it.c == c[2]) {
        SegTree::insert(0, remap[it.x], 1, 0, np2-1);
      }

      pre = it.x;
    }
  } while (next_permutation(c.begin(), c.end()));

  if (updated) {
    for (Rectangle& rect : sol) {
      for (int i=rot; i<4; i++) {
        rect.rotate();
      }
      rect.fix();
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("gold.in", "r", stdin);
  freopen("gold.out", "w", stdout);
#endif

  for (int n; cin >> n && n; ) {
    np2 = 1<<(32-__builtin_clz(n+2));
    assert(np2 >= n+3 && np2 <= N);

    vector<Point> p;
    for (int i=0; i<n; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      p.push_back({a,b,c});
    }

    ans = 0;
    for (int rot=0; rot<4; rot++) {
      solveT(p, rot);
    }
    for (int rot=0; rot<2; rot++) {
      solve3(p, rot);
    }

    cout << ans << nl;
    for (const Rectangle& rect : sol) {
      cout << rect.a.x << " " << rect.a.y << " " << rect.b.x << " " << rect.b.y << nl;
    }
  }

  return 0;
}
