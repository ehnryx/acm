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

void build(vector<vector<int>>& adj, int u, int p) {
  if(p) adj[u].erase(find(begin(adj[u]), end(adj[u]), p));
  for (int v : adj[u]) {
    build(adj, v, u);
  }
}

int solve(
    const vector<vector<int>>& adj,
    const vector<int>& val,
    vector<vector<int>>& memo,
    int u, int have) {
  if(memo[u][have] != -1) return memo[u][have];
  static const int small = numeric_limits<int>::min();

  if(empty(adj[u])) {
    if(have == 0) {
      return memo[u][have] = 0;
    } else if(have == 1) {
      return memo[u][have] = val[u];
    } else {
      return memo[u][have] = small;
    }
    assert(false);
  }

  int n = adj[u].size();
  vector dp(n + 1, vector(have + 1, vector<int>(2, small)));
  dp[0][0][0] = 0;
  if(have) {
    dp[0][1][1] = 0;
  }
  for(int i=1; i<=n; i++) {
    int v = adj[u][i-1];
    for(int j=0; j<=have; j++) {
      for(int put=0; put<=j; put++) {
        int cur = solve(adj, val, memo, v, put);
        if(cur < 0) continue; // sad
        if(put % 2 == 0) {
          // all even
          dp[i][j][0] = max(dp[i][j][0], dp[i-1][j-put][0] + cur);
          // had odd
          dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-put][1] + cur);
        } else {
          // was even
          dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-put][0] + cur);
          // was odd
          dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-put][1] + cur);
        }
      }
    }
  }

  return memo[u][have] = max(dp[n][have][0], dp[n][have][1] + val[u]);
}

void solve_case() {

  static const int big = numeric_limits<int>::max() / 2;

  int n, m;
  cin >> n >> m;

  vector<int> val(n+1);
  for(int i=1; i<=n; i++) {
    cin >> val[i];
  }

  vector<vector<int>> adj(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  build(adj, 1, 0);

  if(m == 0) {
    cout << val[1] << nl;
    return;
  }

  val[1] += big;
  int ans = val[1];
  vector memo(n+1, vector<int>(2*m + 1, -1));
  for(int sad=0; sad<=m; sad++) {
    ans = max(ans, solve(adj, val, memo, 1, 2*sad));
  }
  cout << ans - big << nl;

  return;
}

void initialize() {
}

