#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const vector<int> dx = {0, 1, 0, -1};
const vector<int> dy = {-1, 0, 1, 0};

void solve(int n, int m) {
  //cerr << "SOLVE " << n << " " << m << nl;

  function<int(int,int)> get = [=](int i, int j) {
    if(i == 0 || j == 0 || i > n || j > m) return n*m;
    return m*(i-1) + (j-1);
  };

  vector<vector<int>> adj(n*m + 1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      char cell;
      cin >> cell;
      int bm = stoi(string(1, cell), 0, 16);
      for(int d=0; d<4; d++) {
        if(bm & 1<<d) continue;
        int ni = i + dx[d];
        int nj = j + dy[d];
        adj[get(i, j)].push_back(get(ni, nj));
        if(get(ni, nj) == n*m) {
          adj[get(ni, nj)].push_back(get(i, j));
        }
      }
    }
  }

  if(adj[n*m].size() != 2) {
    cout << "NO SOLUTION" << nl;
    return;
  }

  int s = adj[n*m].front();
  int t = adj[n*m].back();
  adj[n*m].clear();

  vector<bool> vis(n*m + 1);
  bool reach = false;
  bool multi = false;
  function<void(int,int)> dfs = [&](int u, int p) {
    assert(!vis[u]);
    vis[u] = true;
    if(u == t) reach = true;
    for(int v : adj[u]) {
      if(!vis[v]) {
        dfs(v, u);
      } else if(v != p && v != n*m) {
        multi = true;
      }
    }
  };
  dfs(s, -1);

  int sum = accumulate(vis.begin(), vis.end(), (int)0);
  if(!reach) {
    cout << "NO SOLUTION" << nl;
  } else if(sum < n*m + 1) {
    cout << "UNREACHABLE CELL" << nl;
  } else if(multi) {
    cout << "MULTIPLE PATHS" << nl;
  } else {
    cout << "MAZE OK" << nl;
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(int n, m; cin >> n >> m && n; ) {
    solve(n, m);
  }

  return 0;
}
