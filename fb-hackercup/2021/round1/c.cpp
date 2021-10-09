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

#include "../../../../lca/number/mod_int.h"
using Int = mod_int<MOD>;

Int solve_tree(int n, const vector<vector<pair<int, int>>>& adj, vector<Int>& res) {
  vector<int> sz(n+1), par(n+1);

  function<int(int, int, vector<int>&)> build = [&](int u, int p, vector<int>& all) {
    par[u] = p;
    all.push_back(u);
    sz[u] = 1;
    for(auto [v, e] : adj[u]) {
      if(e == p) continue;
      sz[u] += build(v, e, all);
    }
    return sz[u];
  };

  Int total = 0;
  for(int i=1; i<=n; i++) {
    if(sz[i]) continue;
    vector<int> all;
    int cur = build(i, 0, all);
    total += (ll)cur * (cur - 1) / 2;
    for(int j : all) {
      if(!par[j]) continue;
      res[par[j]] += (ll)sz[j] * (cur - sz[j]);
    }
  }

  return total;
}

void solve_case() {

  static const int M = 20;

  int n;
  cin >> n;
  vector adj(M, vector<vector<pair<int, int>>>(n+1));
  for(int i=1; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    assert(c <= M);
    for(int j=0; j<c; j++) {
      adj[j][a].emplace_back(b, i);
      adj[j][b].emplace_back(a, i);
    }
  }

  Int total = 0;
  vector<Int> res(n+1);
  for(int j=0; j<M; j++) {
    total += solve_tree(n, adj[j], res);
  }

  Int ans = 1;
  for(int i=1; i<n; i++) {
    ans *= total - res[i];
  }
  cout << ans << nl;

  return;
}

void initialize() {
}

