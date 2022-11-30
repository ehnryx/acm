#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
namespace {
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
}

using ll = long long;
using ld = long double;
using pt = complex<ld>;
random_device _rd; mt19937 rng(_rd());

constexpr char nl = '\n';

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

namespace ubc {
using pol = vector<pt>;
constexpr ld EPS = 1e-9;
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS
    ||  (a.real()<=b.real()+EPS && a.imag()<b.imag()-EPS); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS
    ||  (a.imag()<=b.imag()+EPS && a.real()<b.real()-EPS); }
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1, n=p.size();
  pol ch(2*n); for (int i = 0, d = 1; i < n && i >= 0; i += d) {
    // If no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top>bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2])<=0) top--;
    ch[top++] = p[i]; if (i == n-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch; }
}

void solve_case() {

  int n, k, d;
  cin >> n >> k >> d;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }
  v = ubc::chull(v);
  sort(begin(v), end(v), ubc::cmp_lex);
  v.resize(distance(begin(v), unique(begin(v), end(v))));

  auto get_dist = [&v](int i, int j) -> ll {
    int dx = (int)real(v[i]) - (int)real(v[j]);
    int dy = (int)imag(v[i]) - (int)imag(v[j]);
    return (ll)dx*dx + (ll)dy*dy;
  };

  n = size(v);
  constexpr auto big = numeric_limits<ll>::max();
  vector<ll> dist(n, big);
  vector<bool> vis(n);
  dist[0] = 0;
  while(!vis[n-1]) {
    int u = n-1;
    for(int i=0; i<n-1; i++) {
      if(!vis[i] && dist[i] < dist[u]) {
        u = i;
      }
    }
    if(dist[u] == big) break;
    for(int i=0; i<n; i++) {
      if(vis[i]) continue;
      ll cost = get_dist(u, i);
      if(cost <= (ll)d*d) {
        dist[i] = min(dist[i], dist[u] + max((ll)k, cost));
      }
    }
    vis[u] = true;
  }

  if(!vis[n-1]) {
    cout << -1 << nl;
  } else {
    cout << dist[n-1] << nl;
  }

  return;
}

void initialize() {
}

