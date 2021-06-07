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
random_device _rd; mt19937 rng(_rd());

const int N = 60;
ll ans[N][N];
ll solve(int a, int b) {
  vector<vector<pair<int,int>>> layer(N*N);
  vector cnt(N, vector<ll>(N));
  cnt[a][b] = 1;
  vector adj(N, vector<vector<pair<int,int>>>(N));
  vector dist(N, vector<int>(N, -1));
  queue<pair<int,int>> bfs;
  bfs.emplace(a, b);
  dist[a][b] = 0;
  while(!bfs.empty()) {
    tie(a, b) = bfs.front();
    bfs.pop();
    layer[dist[a][b]].emplace_back(a, b);
    if(int add = (a > 0 || b > 1); b > 0 && a + add < N) {
      if(dist[a+add][b-1] == -1) {
        dist[a+add][b-1] = dist[a][b] + 1;
        bfs.emplace(a+add, b-1);
      }
      if(dist[a+add][b-1] == dist[a][b] + 1) {
        adj[a][b].emplace_back(a+add, b-1);
      }
    }
    if(int add = (a > 2 || b > 0); a > 1) {
      if(dist[a-2+add][b] == -1) {
        dist[a-2+add][b] = dist[a][b] + 1;
        bfs.emplace(a-2+add, b);
      }
      if(dist[a-2+add][b] == dist[a][b] + 1) {
        adj[a][b].emplace_back(a-2+add, b);
      }
    }
    if(int add = (a > 1 || b > 0); a > 0) {
      if(dist[a-1+add][b] == -1) {
        dist[a-1+add][b] = dist[a][b] + 1;
        bfs.emplace(a-1+add, b);
      }
      if(dist[a-1+add][b] == dist[a][b] + 1) {
        adj[a][b].emplace_back(a-1+add, b);
      }
    }
  }

  for(int d=0; d<dist[0][0]; d++) {
    for(auto [i, j] : layer[d]) {
      for(auto [x, y] : adj[i][j]) {
        cnt[x][y] += cnt[i][j];
      }
    }
  }
  return cnt[0][0];
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

  for(int i=0; i<=20; i++) {
    for(int j=0; j<=20; j++) {
      ans[i][j] = solve(i, j);
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int a, b;
    cin >> a >> b;
    cout << ans[a][b] << nl;
  }

  return 0;
}
