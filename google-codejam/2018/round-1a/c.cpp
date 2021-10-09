#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

ld sqr(ld x) { return x*x; }

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

void caseinit() {
}

// Stores a set of disconnected intervals, amortized O(log n) / operation
// interval is inclusive / exclusive [a, b), find returns interval or {INF,INF}
struct interval_set { set<pair<ld, ld>> s;
  void insert(ld a, ld b) { if (s.empty()) { s.insert({a, b}); return; }
    //! extend right (intervals starting > a)
    auto it1 = s.upper_bound({a, INF}); while (it1 != s.end()) {
      if ((*it1).first <= b) { auto it1nxt = it1; ++it1nxt;
        b = max(b, (*it1).second); s.erase(it1); it1 = it1nxt; } else break; }
    //! extend left (intervals starting <= a)
    it1 = s.upper_bound({a, INF}); if (it1 != s.begin()) { --it1; while (1) {
      if (a <= (*it1).second) { auto it1nxt = it1; --it1nxt;
        bool isBegin = (it1 == s.begin());
        a = min(a, (*it1).first); b = max(b, (*it1).second);
        s.erase(it1); it1 = it1nxt; if (isBegin) break; } else break; } }
    s.insert({a, b}); }
  pair<ld, ld> find(ld x) { if (s.empty()) return {INF, INF};
    auto it1 = s.upper_bound({x, INF});
    if (it1 == s.begin()) return {INF, INF}; --it1;
    if ((*it1).second <= x) return {INF, INF}; return *it1; } 
};

const int N = 100 + 1;
int width[N], height[N];

void solve() {
  caseinit();

  int n, perim;
  cin >> n >> perim;

  interval_set iset;
  iset.insert(0, 100*EPS);

  ld sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> width[i] >> height[i];
    sum += 2 * (width[i] + height[i]);

    vector<pair<ld,ld>> segs;
    for (const pair<ld,ld>& seg : iset.s) {
      segs.push_back(seg);
    }
    for (const pair<ld,ld>& seg : segs) {
      iset.insert(
          seg.first + 2 * min(width[i], height[i]), 
          seg.second + 2 * sqrt(sqr(width[i]) + sqr(height[i]))
      );
    }
    //cerr << i << ": " << iset.s << endl;
  }

  perim -= sum;
  auto it = iset.s.upper_bound({perim + EPS, (ld)INF});
  if (it != iset.s.begin() && (*prev(it)).second > perim - EPS) {
    cout << sum + perim << nl;
  } else {
    cout << sum + (*prev(it)).second << nl;
  }

  return;
}

