#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
  ld x; int t, i;
  bool operator < (const Point& o) const {
    return x < o.x;
  }
};

const ld PI = acos((ld)-1);

const int N = 1e5+1;
pt p[N];

int count(int n, ld r) {
  vector<Point> v;
  For(i,n) {
    ld d = abs(p[i]);
    ld a = arg(p[i]);
    ld b = acos(r/d);
    ld s = a-b;
    if (s<-PI) s += 2*PI;
    ld t = a+b;
    if (t>PI) t -= 2*PI;

    if (s < t) {
      v.push_back({s,1,i});
      v.push_back({t,-1,i});
      v.push_back({s+2*PI,1,i});
      v.push_back({t+2*PI,-1,i});
    } else {
      v.push_back({s,1});
      v.push_back({t+2*PI,-1});
    }
  }
  sort(v.begin(), v.end());

  map<int,int> memo;
  unordered_set<int> active;
  memo[0] = 0;
  int cur = 0;
  int tot = 0;
  int idx = 0;
  for (const Point& it : v) {
    if (it.t == -1 && active.count(it.i)) {
      memo[tot] = ++idx;
      active.clear();
      cur = 0;
    } else {
      cur++;
      tot++;
      active.insert(it.i);
    }
  }
  assert(memo[0] == 0);

  int ans = INF;
  for (const pii& it : memo) {
    auto jt = memo.upper_bound(it.first-n);
    if (jt != memo.begin()) {
      ans = min(ans, it.second - prev(jt)->second);
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  ld minv = INF;
  For(i,n) {
    int x, y;
    cin >> x >> y;
    p[i] = pt(x,y);
    minv = min(minv, abs(p[i]));
  }

  ld left = 0;
  ld right = minv;
  for (int bs=0; bs<49; bs++) {
    ld mid = (left+right)/2;
    if (count(n, mid) <= m) {
      left = mid;
    } else {
      right = mid;
    }
  }
  cout << left << nl;

  return 0;
}
