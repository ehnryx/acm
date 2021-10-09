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

struct Item {
  ll x, c;
  bool operator < (const Item& o) const {
    return c < o.c;
  }
};

template <class T, bool lin=true, bool rin=false>
struct IntervalSet { T inf; set<pair<T,T>> s;
  IntervalSet(T inf): inf(inf) {}
  bool cmp(T a, T b, bool l, bool r=false) {
    if (l||r) return a < b || a == b; else return a < b; }
  T insert(T a, T b) {
    if (s.empty()) { s.insert({a,b}); return b-a; }
    T lb = a, ub = b;
    auto it = s.upper_bound({a,inf});
    while (it != s.end() && cmp(it->first,b,lin,rin)) {
      ub = min(ub, it->first);
      b = max(b, it->second); it = s.erase(it); }
    it = s.upper_bound({a,inf});
    while (it != s.begin() && cmp(a,(--it)->second,lin,rin)) {
      lb = max(lb, it->second);
      a = min(a, it->first); b = max(b, it->second); it = s.erase(it); }
    s.insert({a,b}); return max((T)0,ub-lb); }
  pair<T,T> find(T x) {
    if (s.empty()) { return {inf,inf}; }
    auto it = s.upper_bound({x,inf});
    if (it == s.begin()) return {inf,inf};
    if (cmp((--it)->second,x,!rin)) return {inf,inf};
    if (cmp(x,it->first,!lin)) return {inf,inf};
    return *it; } };

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, g;
  cin >> n >> g;

  vector<Item> p;
  p.push_back({0,0});
  ll maxv = 0;
  for (int i=0; i<n; i++) {
    ll d, c;
    cin >> d >> c;
    p.push_back({d,c});
    maxv = max(maxv, d);
  }
  sort(p.begin(), p.end());

  IntervalSet<ll> iset(INFLL);
  iset.insert(maxv, maxv+g);
  ll ans = 0;
  for (const Item& it : p) {
    ans += iset.insert(it.x, it.x+g) * it.c;
  }
  if (iset.s.begin()->second > maxv) {
    cout << ans << nl;
  } else {
    cout << "cancel road trip" << nl;
  }

  return 0;
}
