#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#pragma GCC optimize("fast-math")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "tria"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef __int128 ll;
typedef double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS
    ||  (a.imag()<=b.imag()+EPS && a.real()<b.real()-EPS); }

// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) / abs(a-b) < EPS &&
    dp(b-a, p-a)>0 && dp(a-b, p-b)>0; }

// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const vector<pt> &v, const pt &p) {
  bool res = 0; for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
    res |= on_segment(v[i], v[j], p) || abs(p-v[i]) < EPS; }
  return res; }

// orientation does not matter !!!
bool pt_in_polygon(const pt &p, const vector<pt> &v, bool strict=false) {
  if (on_boundary(v,p)) return !strict;
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p)); }
  return abs(res) > 1; } // will be either 2*PI or 0

vector<pt> chull(vector<pt> p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1, n=p.size();
  vector<pt> ch(2*n); for (int i = 0, d = 1; i < n && i >= 0; i += d) {
    // If no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top>bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2])<=0) top--;
    ch[top++] = p[i]; if (i == n-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
}

ostream& operator << (ostream& os, __int128 v) {
  if(v == 0) return os << "0";
  assert(v > 0);
  string out;
  for( ; v; v/=10) {
    out.push_back(v % 10 + '0');
  }
  reverse(out.begin(), out.end());
  return os << out;
}

const int N = 50;
ll memo[N][N];
ll scary[N][N][N];

ll count(const vector<pt>& v, int h, int a, int b, int c) {
  if(a > b) swap(a, b);
  if(a > c) swap(a, c);
  if(b > c) swap(b, c);
  assert(a < b && b < c);
  if(scary[a][b][c] != -1) return scary[a][b][c];
  ll res = 0;
  vector<pt> t = {v[a], v[b], v[c]};
  for(int i=h; i<v.size(); i++) {
    if(pt_in_polygon(v[i], t, true)) {
      res += count(v, h, a, b, i) * count(v, h, b, c, i) * count(v, h, c, a, i);
    }
  }
  if(res == 0) res = 1;
  return scary[a][b][c] = res;
}

ll solve(const vector<pt>& v, int h, int l, int r) {
  if(memo[l][r] != -1) return memo[l][r];
  if(l+1 >= r) return memo[l][r] = 1;
  ll res = 0;
  for(int i=l+1; i<r; i++) {
    ll cur = solve(v, h, l, i) * solve(v, h, i, r);
    ll cnt = count(v, h, l, i, r);
    res += cur * cnt;
  }
  return memo[l][r] = res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }
  vector<pt> h = chull(v);

  for(int i=0, j=0; i<n; i++) {
    if(!pt_in_polygon(v[i], h, true)) {
      swap(v[i], v[j++]);
    }
  }
  for(int i=0; i<h.size(); i++) {
    v[i] = h[i];
  }

  memset(memo, -1, sizeof memo);
  memset(scary, -1, sizeof scary);
  cout << solve(v, h.size(), 0, (int)h.size()-1) << nl;

	return 0;
}
