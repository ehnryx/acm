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

struct SegmentTree {
  int n;
  vector<ll> st;
  SegmentTree(int _n) {
    n = 1 << (32 - __builtin_clz(max(1, _n - 1)));
    st.resize(2*n);
  }
  void update(ll& a, ll b) { a = gcd(a, b); }
  void insert(int l, int r, ll v) {
    for(l+=n, r+=n; l<r; l/=2, r/=2) {
      if(l&1) update(st[l++], v);
      if(r&1) update(st[--r], v);
    }
  }
  ll query(int i) const {
    ll res = st[i += n];
    for(i/=2; i; i/=2) {
      res = gcd(res, st[i]);
    }
    return res;
  }
};

void solve_case() {

  int n, m;
  cin >> n >> m;
  vector<tuple<ll,int,int,ll>> ev;
  vector<vector<int>> adj(n + 1);
  for(int i=1; i<n; i++) {
    int a, b; ll lim, toll;
    cin >> a >> b >> lim >> toll;
    ev.emplace_back(lim, a, b, toll);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for(int i=0; i<m; i++) {
    int c, w;
    cin >> c >> w;
    ev.emplace_back(w, n + 1, c, i);
  }
  sort(begin(ev), end(ev));

  vector<int> sub(n + 1), start(n + 1), par(n + 1);
  int sid = 0;
  function<void(int,int)> build = [&](int u, int p) {
    par[u] = p;
    start[u] = sid++;
    sub[u] = 1;
    for(int v : adj[u]) {
      if(v == p) continue;
      build(v, u);
      sub[u] += sub[v];
    }
  };
  build(1, 0);

  SegmentTree st(n);
  vector<ll> ans(m);
  for(auto [_, a, b, c] : ev) {
    if(a > n) {
      ans[c] = st.query(start[b]);
    } else {
      if(par[b] == a) swap(a, b);
      st.insert(start[a], start[a] + sub[a], c);
    }
  }

  for(ll it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return;
}

void initialize() {
}

