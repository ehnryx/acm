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

ll sqr(ll n) { return n*n; }
ll dist(pair<int, int> a, pair<int, int> b) {
  return sqr(a.first - b.first) + sqr(a.second - b.second);
}

char dp[1 << 21];

char solve(
    const vector<pair<int, int>>& child,
    const vector<pair<int, int>>& candy,
    int bm, vector<pair<int, int>>& ans) {
  if((bm & 1) == 0) return false;
  if(__builtin_popcount(bm) == 1) {
    return bm == 1;
  }
  if(dp[bm] != -1) return dp[bm];

  int n = size(child);
  for(int i=0; i<n; i++) {
    if(!(bm & 1<<(i+n+1))) continue;
    ll mindist = numeric_limits<ll>::max();
    for(int j=0; j<n+1; j++) {
      if(!(bm & 1<<j)) continue;
      mindist = min(mindist, dist(child[i], candy[j]));
    }
    for(int j=0; j<n+1; j++) {
      if(!(bm & 1<<j) || dist(child[i], candy[j]) != mindist) continue;
      if(solve(child, candy, bm ^ (1 << (i + n+1)) ^ (1 << j), ans)) {
        ans.emplace_back(i+1, j+1);
        return true;
      }
    }
  }

  return dp[bm] = false;
}

void solve_case() {

  int n;
  cin >> n;
  vector<pair<int, int>> child(n), candy(n+1);
  for(int i=0; i<n; i++) {
    cin >> child[i].first >> child[i].second;
  }
  for(int i=0; i<n+1; i++) {
    cin >> candy[i].first >> candy[i].second;
  }

  memset(dp, -1, sizeof(dp[0]) * (1 << (2*n + 1)));
  vector<pair<int, int>> ans;
  if(solve(child, candy, (1 << (2*n + 1)) - 1, ans)) {
    reverse(begin(ans), end(ans));
    cout << "POSSIBLE" << nl;
    for(auto [x, y] : ans) {
      cout << x << " " << y << nl;
    }
  } else {
    cout << "IMPOSSIBLE" << nl;
  }

  return;
}

void initialize() {
}

