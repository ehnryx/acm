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
random_device _rd; mt19937 rng(_rd());

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

template <class T = int>
vector<T> read_array(int n, int s=0) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T = int>
vector<vector<T>> read_grid(int n, int m, int s=0, int t=0) {
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
    auto start = chrono::steady_clock::now();
		cout << "Case #" << cc << ": ";
		solve_case();
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

void solve1(int n, int m, vector<pair<string,int>>& all) {
  cerr << "solve " << n << nl;

  auto [a, s] = all[0];
  if(2*s >= m) {
    cout << a << " " << s << "/1" << nl;
  } else {
    transform(begin(a), end(a), begin(a), [](char c) { return c ^ 'T' ^ 'F'; });
    cout << a << " " << m-s << "/1" << nl;
  }
}

void solve2(int n, int m, vector<pair<string,int>>& all) {
  cerr << "solve " << n << nl;

  auto [a1, s1] = all[0];
  auto [a2, s2] = all[1];
  vector<int> same, different;
  for(int i=0; i<m; i++) {
    if(a1[i] == a2[i]) {
      same.push_back(i);
    } else {
      different.push_back(i);
    }
  }

  assert((s1 + s2 - size(different)) % 2 == 0);
  int x = (s1 + s2 - size(different)) / 2;
  int y = s1 - x;

  string res = a1;
  if(2*x < size(same)) {
    for(int i : same) {
      res[i] ^= 'T' ^ 'F';
    }
    x = size(same) - x;
  }
  if(2*y < size(different)) {
    for(int i : different) {
      res[i] ^= 'T' ^ 'F';
    }
    y = size(different) - y;
  }

  cout << res << " " << x + y << "/1" << nl;
}

void solve3(int, int, vector<pair<string,int>>&);

void solve_case() {

	int n, m;
  cin >> n >> m;
  auto all = read_array<pair<string,int>>(n);

  if(n == 1) {
    solve1(n, m, all);
  } else if(n == 2) {
    solve2(n, m, all);
  } else {
    solve3(n, m, all);
  }

	return;
}

void initialize() {
}

void solve3(int n, int m, vector<pair<string,int>>& all) {
  cerr << "solve " << n << nl;

  auto [a1, s1] = all[0];
  auto [a2, s2] = all[1];
  auto [a3, s3] = all[2];
  vector<int> same, g12, g23, g31;
  for(int i=0; i<m; i++) {
    if(a1[i] == a2[i] && a2[i] == a3[i]) {
      same.push_back(i);
    } else if(a1[i] == a2[i]) {
      g12.push_back(i);
    } else if(a2[i] == a3[i]) {
      g23.push_back(i);
    } else {
      g31.push_back(i);
    }
  }
  cerr << "equations: " << nl;
  cerr << "x1 + y1 + z1 + w1 = " << s1 << nl;
  cerr << "x2 + y2 + z2 + w2 = " << s2 << nl;
  cerr << "x3 + y3 + z3 + w3 = " << s3 << nl;
  cerr << "x1 - x2 = " << 0 << nl;
  cerr << "x2 - x3 = " << 0 << nl;
  cerr << "y1 - y2 = " << 0 << nl;
  cerr << "y2 + y3 = " << size(g12) << nl;
  cerr << "z2 - z3 = " << 0 << nl;
  cerr << "z3 + z1 = " << size(g23) << nl;
  cerr << "w3 - w1 = " << 0 << nl;
  cerr << "w1 + w2 = " << size(g31) << nl;
  cerr << nl;
}

