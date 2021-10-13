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



void solve_case() {

  int n, m;
  cin >> n >> m;
  vector h(n, vector<int>(m)), s(n, vector<int>(m));
  vector<tuple<int, int, int>> ev;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> h[i][j];
      ev.emplace_back(2*h[i][j], i, j);
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> s[i][j];
      ev.emplace_back(2*s[i][j] + 1, i, j);
    }
  }
  sort(begin(ev), end(ev), greater<>());

  vector<int> dsu(n*m, -1);
  vector<int> have(n*m, 0);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int, int)> link = [&](int i, int j) {
    i = find(i);
    j = find(j);
    if(i == j) return;
    dsu[i] = j;
    have[j] += have[i];
  };

  function<int(int, int)> get = [&](int i, int j) {
    return i*m + j;
  };

  int ans = 0;
  int need = 0;
  vector alive(n, vector<bool>(m));
  for(auto [height, i, j] : ev) {
    if(height % 2 == 0) {
      alive[i][j] = true;
      for(auto [di, dj] : {
          pair(1, 0), pair(-1, 0), pair(0, 1), pair(0, -1) }) {
        int ni = i + di;
        int nj = j + dj;
        if(0 <= ni && ni < n && 0 <= nj && nj < m && alive[ni][nj]) {
          link(get(i, j), get(ni, nj));
        }
      }
    } else if(alive[i][j]) {
      int ref = find(get(i, j));
      if(have[ref] == 0) {
        need += 1;
        have[ref] = 1;
      }
      ans += 1;
    }
  }

  cout << ans << " " << need << nl;

  return;
}

void initialize() {
}

