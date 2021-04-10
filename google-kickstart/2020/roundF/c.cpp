//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9+7;
constexpr ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ", " << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[ "; for (const T& it : v) { os << it << " , "; }
  return os << ']';
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) { os << it << " , "; }
	return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) { os << it << " , "; }
	return os << '}';
}

template <class T, class U>
istream& operator >> (istream& is, pair<T,U>& v) {
  return is >> v.first >> v.second;
}
template <int i, class... Ts>
istream& read_tuple_impl(istream& is, tuple<Ts...>& v) {
  if constexpr (i == 0) return is;
  else return read_tuple_impl<i-1>(is, v) >> get<i-1>(v);
}
template <class... Ts>
istream& operator >> (istream& is, tuple<Ts...>& v) {
  return read_tuple_impl<sizeof...(Ts)>(is, v);
}

template <class T>
vector<T> read_array(int n, int s=1) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T>
vector<vector<T>> read_grid(int n, int m, int s=1, int t=1) {
  vector a(n + 2*s, vector<T>(m + 2*t));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[s+i][t+j];
    }
  }
  return a;
}

void solve_case();
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

  initialize();

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cout << "Case #" << cc << ": ";
		solve_case();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

#define idx(x, y) (((x)-1)*((x)-1) + (y) - 1)

bool stuck(int n, int x, int y, ll bm) {
  if(y > 1 && !(bm >> idx(x, y-1) & 1)) return false;
  if(y < 2*x-1 && !(bm >> idx(x, y+1) & 1)) return false;
  if(y % 2 == 0 && !(bm >> idx(x-1, y-1) & 1)) return false;
  if(y % 2 == 1 && x < n && !(bm >> idx(x+1, y+1) & 1)) return false;
  return true;
}

int solve(int n, int xa, int ya, int xb, int yb, ll bm) {
  if(stuck(n, xa, ya, bm)) {
    if(stuck(n, xb, yb, bm)) return 0;
    else return -solve(n, xb, yb, xa, ya, bm);
  }

  int res = -INF;
  int x = xa, y = ya;
  if(y > 1 && !(bm >> idx(x, y-1) & 1)) {
    res = max(res, 1 - solve(n, xb, yb, xa, ya-1, bm | 1LL << idx(x, y-1)));
  }
  if(y < 2*x-1 && !(bm >> idx(x, y+1) & 1)) {
    res = max(res, 1 - solve(n, xb, yb, xa, ya+1, bm | 1LL << idx(x, y+1)));
  }
  if(y % 2 == 0 && !(bm >> idx(x-1, y-1) & 1)) {
    res = max(res, 1 - solve(n, xb, yb, xa-1, ya-1, bm | 1LL << idx(x-1, y-1)));
  }
  if(y % 2 == 1 && x < n && !(bm >> idx(x+1, y+1) & 1)) {
    res = max(res, 1 - solve(n, xb, yb, xa+1, ya+1, bm | 1LL << idx(x+1, y+1)));
  }
  return res;
}

void solve_case() {

  int n, ra, pa, rb, pb, c;
	cin >> n >> ra >> pa >> rb >> pb >> c;

  ll bad = 1LL << idx(ra, pa) | 1LL << idx(rb, pb);
  for(auto [x, y] : read_array<pair<int,int>>(c, 0)) {
    bad |= 1LL << idx(x, y);
  }
  cout << solve(n, ra, pa, rb, pb, bad) << nl;

	return;
}

void initialize() {
}

