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
  string percentage;
  cin >> percentage;
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

  static const int n = 100;
  static const int m = 10000;
  vector<vector<char>> a(n);
  for(int i=0; i<n; i++) {
    a[i] = read_array<char>(m);
  }

  vector<double> s(n), q(m);
  for(int i=0; i<n; i++) {
    int cnt = 0;
    for(int j=0; j<m; j++) {
      cnt += (a[i][j] == '1');
    }
    double p = (double)cnt / m;
    s[i] = p*6 - 3;
  }
  for(int j=0; j<m; j++) {
    int cnt = 0;
    for(int i=0; i<n; i++) {
      cnt += (a[i][j] == '0');
    }
    double p = (double)cnt / n;
    q[j] = p*6 - 3;
  }

  pair<double,int> ans(-1, -1);
  for(int i=0; i<n; i++) {
    int cnt = 0;
    int solved = 0;
    for(int j=0; j<m; j++) {
      if(q[j] >= s[i]) {
        cnt++;
        solved += (a[i][j] == '1');
      }
    }
    assert(cnt > 0);
    ans = max(ans, pair((double)solved / cnt, i));
  }
  cout << ans.second + 1 << nl;

  return;
}

void initialize() {
}

