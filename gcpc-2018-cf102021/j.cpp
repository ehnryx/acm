//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 3e5 + 7;
const int M = 4*N + 7;
vector<int> adj[N];
int edge[M];
bool have[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  vector<int> corners;
  for(int i=1; i<=n; i++) {
    for(int j=0; j<4; j++) {
      int e;
      cin >> e;
      adj[i].push_back(e);
      if(e) {
        edge[e] ^= i;
      }
    }

    for(int j=4-1, k=0; k<4; j=k++) {
      if(adj[i][j] == adj[i][k]) {
        corners.push_back(i);
        break;
      }
    }
  }

  if(corners.size() > 4 || corners.empty()) {
    cout << "impossible" << nl;
    return 0;
  }

  vector<vector<int>> grid(1);
  have[corners[0]] = true;
  grid[0].push_back(corners[0]);
  while(adj[corners[0]][0] || adj[corners[0]][1]) {
    rotate(adj[corners[0]].begin(), adj[corners[0]].begin() + 1, adj[corners[0]].end());
  }
  while(adj[grid[0].back()][3]) {
    int u = grid[0].back();
    int e = adj[u][3];
    int v = edge[e] ^ u;
    if(!e || have[v]) {
      cout << "impossible" << nl;
      return 0;
    }
    have[v] = true;
    grid[0].push_back(v);
    while(adj[v][1] != e) {
      rotate(adj[v].begin(), adj[v].begin() + 1, adj[v].end());
    }
    if(adj[grid[0].back()][0]) {
      cout << "impossible" << nl;
      return 0;
    }
  }
  int length = grid[0].size();

  int row = 1;
  for( ; ; row++) {
    int open = 0;
    for(int u : grid.back()) {
      open += (adj[u][2] > 0);
    }
    if(open == 0) break;
    if(open != grid.back().size()) {
      cout << "impossible" << nl;
      return 0;
    }

    grid.push_back(vector<int>());
    for(int u : grid[row-1]) {
      int e = adj[u][2];
      int v = edge[e] ^ u;
      if(!e || have[v]) {
        cout << "impossible" << nl;
        return 0;
      }
      have[v] = true;
      grid[row].push_back(v);
      rotate(adj[v].begin(), find(adj[v].begin(), adj[v].end(), e), adj[v].end());
    }
    assert(grid.back().size() == length);

    if(adj[grid[row][0]][1]) {
      cout << "impossible" << nl;
      return 0;
    }
    if(adj[grid[row][length-1]][3]) {
      cout << "impossible" << nl;
      return 0;
    }
    for(int i=0; i+1<length; i++) {
      if(adj[grid.back()[i]][3] == 0) {
        cout << "impossible" << nl;
        return 0;
      }
      if(adj[grid[row][i]][3] != adj[grid[row][i+1]][1]) {
        cout << "impossible" << nl;
        return 0;
      }
    }
  }

  if(row * length < n) {
    cout << "impossible" << nl;
    return 0;
  }

  assert(row * length == n);
  cout << row << " " << length << nl;
  for(int i=0; i<row; i++) {
    for(int j=0; j<length; j++) {
      if(grid[i][j] < 1 || grid[i][j] > n) for(;;);
      cout << grid[i][j] << " ";
    }
    cout << nl;
  }

  return 0;
}
