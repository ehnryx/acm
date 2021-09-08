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

struct DSU {
  int n, m, len;
  vector<int> dsu;
  DSU(int _n, int _m): n(_n), m(_m), len(n*m), dsu(len, -1) {}
  pair<int, int> find(int i, int j) {
    int res = find(i*m + j);
    return pair(res / m, res % m);
  }
  int find(int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  }
  void link(int i, int j, int a, int b) {
    link(i*m + j, a*m + b);
  }
  void link(int i, int j) {
    i = find(i);
    j = find(j);
    if(i == j) return;
    dsu[i] = j;
  }
};

void solve_case() {

  int n, m;
  cin >> n >> m;
  vector g(n+2, vector<char>(m+2, '#'));
  int ans = 0;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
      ans -= !!isalpha(g[i][j]);
    }
  }

  DSU dsu(n+2, m+2);
  for(int i=1; i<=n; i++) {
    for(int j=1, wall=0; j<=m+1; j++) {
      if(g[i][j] == '#') {
        for(int k=1; wall+k < j-k; k++) {
          dsu.link(i, wall+k, i, j-k);
        }
        wall = j;
      }
    }
  }
  for(int j=1; j<=m; j++) {
    for(int i=1, wall=0; i<=n+1; i++) {
      if(g[i][j] == '#') {
        for(int k=1; wall+k < i-k; k++) {
          dsu.link(wall+k, j, i-k, j);
        }
        wall = i;
      }
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(isalpha(g[i][j])) {
        auto [a, b] = dsu.find(i, j);
        assert(g[a][b] == '.' || g[a][b] == g[i][j]);
        g[a][b] = g[i][j];
      }
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      auto [a, b] = dsu.find(i, j);
      g[i][j] = g[a][b];
      ans += !!isalpha(g[i][j]);
    }
  }

  cout << ans << nl;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cout << g[i][j];
    }
    cout << nl;
  }

  return;
}

void initialize() {
}

