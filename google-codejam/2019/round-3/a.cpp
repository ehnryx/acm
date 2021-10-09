#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

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

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T, W;
  cin >> T >> W;
  for (int cc = 1; cc <= T; cc++) {
    //cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

// Stores a set of disconnected intervals, amortized O(log n) / operation
// interval is inclusive / exclusive [a, b), find returns interval or {INF,INF}
struct interval_set { set<pair<ll, ll>> s;
void insert(ll a, ll b) { if (s.empty()) { s.insert({a, b}); return; }
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
pair<ll, ll> find(ll x) { if (s.empty()) return {INF, INF};
  auto it1 = s.upper_bound({x, INF});
  if (it1 == s.begin()) return {INF, INF}; --it1;
  if ((*it1).second <= x) return {INF, INF}; return *it1; }
};

inline ll input() {
  ll v;
  cin >> v;
  assert(v != -1);
  if (v < 0) return false;
  else return v;
}

void caseinit() {
}

const ll L = 1e12;
const ll M = L/2;
const ll S = 1e10;

void solve() {
  caseinit();

  for (ll left; left = input(); ) {
    ll m = (left+left+S-1)/2;
    if (m <= M) {
    } else {
    }
  }

  return;
}

