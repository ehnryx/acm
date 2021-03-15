//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    ll g = abs(__gcd(a, b));
    n = a/g; d = b/g;
    if(d < 0) { n = -n; d = -d; }
  }
  bool operator < (const Frac& o) const { return n*o.d < d*o.n; }
  bool operator == (const Frac& o) const { return n*o.d == d*o.n; }
  Frac operator - () const { return Frac(-n, d); }
  Frac operator + (const Frac& o) const { return Frac(n*o.d + d*o.n, d*o.d); }
  Frac operator - (const Frac& o) const { return Frac(n*o.d - d*o.n, d*o.d); }
  Frac operator / (const Frac& o) const { return Frac(n*o.d, d*o.n); }
  ld value() const { return (ld)n/d; }
};

struct Line {
  ld m, b; Frac s;
  Line(ld _m, ld _b): m(_m), b(_b) {}
  Line(const pair<Frac,Frac>& u, const pair<Frac,Frac>& v) {
    s = (u.second - v.second) / (u.first - v.first);
    m = s.value();
    b = u.second.value() - m * u.first.value();
  }
  bool operator < (const Line& o) const { return pair(-s, b) < pair(-o.s, o.b); }
  Line operator + (const Line& o) const { return Line(m + o.m, b + o.b); }
  Line operator - (const Line& o) const { return Line(m - o.m, b - o.b); }
  ld get(ld x) { return m*x + b; }
};

ld intersect(const Line& u, const Line& v) {
  return (v.b - u.b) / (u.m - v.m);
}

Frac project(int a, int b, int x, int y) {
  return Frac(x) - Frac((ll)(x-a)*y, y-b);
}

void solve() {
  int n, w, h, m;
  cin >> n >> w >> h >> m;

  static const Frac zero(0), one(1);
  vector<Line> lines;
  lines.emplace_back(pair(zero, one), pair(Frac(h), one)); // 0 is positive
  lines.emplace_back(pair(zero, zero), pair(Frac(h), zero)); // 1 is negative
  for(int i=0; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if(a > b) swap(a, b);
    Frac ls = project(a, c, 0, h);
    Frac rs = project(b, c, 0, h);
    Frac lt = project(a, c, w, h);
    Frac rt = project(b, c, w, h);
    lines.emplace_back(pair(ls, zero), pair(lt, one)); // 0 is positive
    lines.emplace_back(pair(rs, zero), pair(rt, one)); // 1 is negative
  }

  vector<tuple<ld,int,int>> events;
  for(int i=0; i<m; i++) {
    int x;
    cin >> x;
    events.emplace_back(x, -1, i);
  }

  n = lines.size();
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      if(lines[i].s == lines[j].s) continue;
      ld x = intersect(lines[i], lines[j]);
      events.emplace_back(x, i, j);
    }
  }
  sort(events.begin(), events.end());

  vector<int> balance(n);
  vector<pair<Line,int>> init_order;
  for(int i=0; i<n; i++) {
    init_order.emplace_back(lines[i], i);
  }
  sort(init_order.begin(), init_order.end());
  int init_balance = 1;
  for(auto [_, i] : init_order) {
    balance[i] = init_balance;
    if(i % 2 == 0) init_balance++;
    else init_balance--;
  }

  vector<ld> ans(m);
  Line sum(0, 1);
  for(auto [x, i, j] : events) {
    if(i == -1) {
      ans[j] = sum.get(x);
    } else {
      if(lines[i].m > lines[j].m) swap(i, j);
      // remove
      for(int t : {i, j}) {
        if(t % 2 == 0 && balance[t] == 0) { // positive
          sum = sum - lines[t];
        }
        if(t % 2 == 1 && balance[t] == 1) { // negative
          sum = sum + lines[t];
        }
      }
      // update
      if(i % 2 == 0) balance[j]++;
      else balance[j]--;
      if(j % 2 == 0) balance[i]--;
      else balance[i]++;
      // insert
      for(int t : {i, j}) {
        if(t % 2 == 0 && balance[t] == 0) { // positive
          sum = sum + lines[t];
        }
        if(t % 2 == 1 && balance[t] == 1) { // negative
          sum = sum - lines[t];
        }
      }
    }
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ":" << nl;
    solve();
  }

  return 0;
}
