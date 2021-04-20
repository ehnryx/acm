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

namespace Tarjan {
const int N = 5e3 + 1;
int low[N],vis[N],scomp[N],scompNum,I;
vector<int> adj[N]; stack<int> verts;
void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
  for (int v : adj[u]) {
    if (!vis[v]) scc(v);
    if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
  if (vis[u] <= low[u]) { int v;
    do { v=verts.top(); verts.pop(); scomp[v]=scompNum; }while (v != u);
    ++scompNum; }}
void get_scc(int n) {
  memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
  scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }
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

  int n;
  cin >> n;
  vector<int> sa(n+1, n), inv(n+1);
  for(int i=1; i<=n; i++) {
    cin >> sa[i];
    sa[i] -= 1;
    inv[sa[i]] = i;
  }
  vector<int> height(n);
  for(int i=1; i<n; i++) {
    cin >> height[i];
  }

  vector dir(n+1, vector<int>(n+1, -1));
  function<void(int,int,int)> add_edge = [&](int i, int j, int c) {
    dir[i][j] = max(dir[i][j], c);
  };
  for(int i=1; i<n; i++) {
    if(height[i] == -1) continue;
    for(int j=0; j<height[i]; j++) {
      add_edge(sa[i] + j, sa[i+1] + j, 0);
      add_edge(sa[i+1] + j, sa[i] + j, 0);
    }
    add_edge(sa[i] + height[i], sa[i+1] + height[i], 1);
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(inv[i] < inv[j]) {
        add_edge(i, j, inv[i+1] > inv[j+1]);
      }
      if(dir[i][j] != -1) {
        Tarjan::adj[i].push_back(j);
      }
    }
  }
  Tarjan::get_scc(n);

  vector dag(Tarjan::scompNum, vector<int>(Tarjan::scompNum, -1));
  vector<int> in(n);
  vector<vector<int>> groups(n);
  for(int i=0; i<n; i++) {
    int id = Tarjan::scomp[i];
    groups[id].push_back(i);
    for(int j=0; j<n; j++) {
      int jd = Tarjan::scomp[j];
      if(dir[i][j] == -1 || id == jd) continue;
      in[jd] += (dag[id][jd] == -1);
      dag[id][jd] = max(dag[id][jd], dir[i][j]);
    }
  }

  vector<int> val(Tarjan::scompNum);
  queue<int> bfs;
  for(int i=0; i<Tarjan::scompNum; i++) {
    if(in[i] == 0) {
      bfs.push(i);
      val[i] = 'a';
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v = 0; v < Tarjan::scompNum; v++) {
      if(dag[u][v] == -1) continue;
      val[v] = max(val[v], val[u] + dag[u][v]);
      if(--in[v] == 0) {
        bfs.push(v);
      }
    }
  }

  string ans(n, 0);
  for(int i=0; i<Tarjan::scompNum; i++) {
    for(int j : groups[i]) {
      ans[j] = val[i];
    }
  }
  cout << ans << nl;

  return 0;
}
